#pragma once

#include <vector>
#include <string>

#include "engine/core/seq/auraseq.h"
#include "engine/core/voice/loaded_voice.h"

namespace auraloid {

struct PhonemeEvent {
    std::string phoneme;
    float start;   // seconds (relative to note start)
    float length;  // seconds
};

class TimingEngine {
public:
    TimingEngine();

    std::vector<PhonemeEvent> generate(
        const Note& note,
        const LoadedVoice& voice,
        float noteDurationSec
    ) const;
};

}
