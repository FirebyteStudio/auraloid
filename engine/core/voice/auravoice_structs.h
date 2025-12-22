#pragma once
#include <cstdint>

namespace auraloid {

struct AuravoiceHeader {
    char     magic[4];      // "AURA"
    uint16_t version;
    uint8_t  voice_type;
    uint8_t  flags;
    uint32_t header_size;
    uint32_t checksum;
};

struct BlockHeader {
    BlockType type;
    uint32_t  size;
    uint32_t  offset;
};

}
