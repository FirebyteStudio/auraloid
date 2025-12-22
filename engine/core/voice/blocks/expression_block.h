#pragma once
#include <vector>
#include "../loaded_voice.h"
#include "../auravoice_reader.h"

namespace auraloid {

class ExpressionBlockParser {
public:
    // Parse EXPRESSION_BLOCK from raw bytes
    static ExpressionSet parse(const std::vector<uint8_t>& data);
};

}
