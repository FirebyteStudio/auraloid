#include "expression_block.h"
#include <stdexcept>
#include <cstring>

namespace auraloid {

// Estrutura interna do bloco
struct RawExpression {
    uint8_t id;
    uint16_t nameLength;
    float min;
    float max;
    // bytes do nome seguem
};

ExpressionSet ExpressionBlockParser::parse(const std::vector<uint8_t>& data) {
    ExpressionSet set;
    size_t offset = 0;

    while (offset + sizeof(RawExpression) <= data.size()) {
        RawExpression raw;
        std::memcpy(&raw, data.data() + offset, sizeof(RawExpression));
        offset += sizeof(RawExpression);

        if (offset + raw.nameLength > data.size())
            throw std::runtime_error("EXPRESSION_BLOCK corrupted (name out of bounds)");

        Expression e;
        e.id = raw.id;
        e.min = raw.min;
        e.max = raw.max;
        e.name = std::string(reinterpret_cast<const char*>(data.data() + offset), raw.nameLength);
        offset += raw.nameLength;

        set.expressions.push_back(e);
    }

    return set;
}

}
