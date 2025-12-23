#pragma once
#include <string>
#include <unordered_map>
#include "../audio/audio_buffer.h"

namespace auraloid {

struct PhonemeSample {
    uint16_t id;
    std::string symbol;
};

class LoadedVoice {
public:
    // Mapa REAL fonema → ID
    std::unordered_map<std::string, uint16_t> phonemeMap;

    // helper
    uint16_t getPhonemeId(const std::string& phoneme) const;
};

}

