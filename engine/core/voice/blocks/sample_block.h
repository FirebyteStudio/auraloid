#pragma once
#include <vector>
#include "../loaded_voice.h"
#include "../auravoice_reader.h"

namespace auraloid {

class SampleBlockParser {
public:
    // Parse SAMPLE_BLOCK from raw bytes
    static std::vector<Sample> parse(const std::vector<uint8_t>& data);
};

}
