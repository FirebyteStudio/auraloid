#include "timing_engine.h"

namespace auraloid {

TimingEngine::TimingEngine() {}

std::vector<PhonemeEvent> TimingEngine::generate(
    const Note& note,
    const LoadedVoice& voice,
    float noteDurationSec
) const {
    std::vector<PhonemeEvent> events;

    // 1️⃣ Resolver sequência de fonemas
    // Por enquanto: 1 fonema explícito OU fallback no lyric
    std::vector<std::string> phonemes;
    if (!note.phoneme.empty()) {
        phonemes.push_back(note.phoneme);
    } else {
        // fallback simples (V1.5): letra inteira = 1 fonema
        phonemes.push_back(note.lyric);
    }

    // 2️⃣ Somar durações base
    float totalBase = 0.0f;
    std::vector<float> baseDurations;

    for (const auto& p : phonemes) {
        float d = voice.getPhonemeBaseDuration(p);
        baseDurations.push_back(d);
        totalBase += d;
    }

    if (totalBase <= 0.0f)
        return events;

    // 3️⃣ Stretch proporcional
    float scale = noteDurationSec / totalBase;
    float cursor = 0.0f;

    for (size_t i = 0; i < phonemes.size(); ++i) {
        float len = baseDurations[i] * scale;

        PhonemeEvent e;
        e.phoneme = phonemes[i];
        e.start = cursor;
        e.length = len;

        events.push_back(e);
        cursor += len;
    }

    return events;
}

}
