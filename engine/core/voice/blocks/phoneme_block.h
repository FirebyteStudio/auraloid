#pragma once
#include <vector>
#include "../loaded_voice.h"
#include "../auravoice_reader.h"

namespace auraloid {

class PhonemeBlockParser {
public:
    // Parse a PHONEME_BLOCK from raw bytes
    static std::vector<Phoneme> parse(const std::vector<uint8_t>& data);
};

}
