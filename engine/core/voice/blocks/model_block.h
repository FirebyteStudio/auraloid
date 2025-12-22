#pragma once
#include <vector>
#include "../loaded_voice.h"
#include "../auravoice_reader.h"

namespace auraloid {

class ModelBlockParser {
public:
    // Parse MODEL_BLOCK from raw bytes
    static NeuralModel parse(const std::vector<uint8_t>& data);
};

}
