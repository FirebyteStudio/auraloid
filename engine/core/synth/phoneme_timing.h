#pragma once
#include <string>
#include <vector>

namespace auraloid {

struct PhonemeSegment {
    std::string phoneme;
    float duration;   // segundos
};

std::vector<PhonemeSegment> splitNotePhonemes(
    const std::string& phonemeStr,
    float noteDurationSec,
    const std::unordered_map<std::string, float>& baseDurations
);

}
