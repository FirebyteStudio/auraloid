#include "phoneme_timing.h"
#include <unordered_map>

namespace auraloid {

std::vector<PhonemeSegment> splitNotePhonemes(
    const std::string& phonemeStr,
    float noteDurationSec,
    const std::unordered_map<std::string, float>& baseDurations
) {
    std::vector<std::string> phonemes;

    // v0.3: split simples por caractere (CV japonês funciona)
    for (char c : phonemeStr) {
        phonemes.emplace_back(1, c);
    }

    float totalBase = 0.0f;
    for (auto& p : phonemes) {
        auto it = baseDurations.find(p);
        totalBase += (it != baseDurations.end())
            ? it->second
            : 0.1f;
    }

    std::vector<PhonemeSegment> result;

    for (auto& p : phonemes) {
        float base =
            baseDurations.count(p)
                ? baseDurations.at(p)
                : 0.1f;

        float ratio = base / totalBase;

        result.push_back({
            p,
            noteDurationSec * ratio
        });
    }

    return result;
}

}
