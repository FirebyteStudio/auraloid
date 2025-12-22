#include "phoneme_block.h"
#include <cstring>
#include <stdexcept>

namespace auraloid {

struct RawPhoneme {
    uint16_t id;
    uint16_t symbolLength;
    float baseDuration;
    // symbol bytes follow immediately
};

std::vector<Phoneme> PhonemeBlockParser::parse(const std::vector<uint8_t>& data) {
    std::vector<Phoneme> phonemes;
    size_t offset = 0;

    while (offset < data.size()) {
        if (offset + sizeof(RawPhoneme) > data.size())
            throw std::runtime_error("PHONEME_BLOCK corrupted or incomplete");

        RawPhoneme raw;
        std::memcpy(&raw, data.data() + offset, sizeof(RawPhoneme));
        offset += sizeof(RawPhoneme);

        if (offset + raw.symbolLength > data.size())
            throw std::runtime_error("PHONEME_BLOCK corrupted (symbol out of bounds)");

        Phoneme p;
        p.id = raw.id;
        p.baseDuration = raw.baseDuration;
        p.symbol = std::string(reinterpret_cast<const char*>(data.data() + offset), raw.symbolLength);
        offset += raw.symbolLength;

        phonemes.push_back(p);
    }

    return phonemes;
}

}
