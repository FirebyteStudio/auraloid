#include "auravoice_reader.h"

#include <fstream>
#include <vector>
#include <cstdint>

// Forward include of Voice (implementation later)
#include <memory>

namespace auraloid {
class Voice;
}

namespace auraloid::voice {

// Minimal binary header for validation (placeholder)
// [0..3]  Magic: 'A','V','O','I'
// [4]     Version major
// [5]     Version minor
struct AuravoiceHeader {
    char magic[4];
    uint8_t major;
    uint8_t minor;
};

static bool readHeader(std::ifstream& file, AuravoiceHeader& out) {
    file.read(reinterpret_cast<char*>(&out), sizeof(AuravoiceHeader));
    return file.good();
}

bool AuravoiceReader::validateHeader(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    AuravoiceHeader header{};
    if (!readHeader(file, header)) {
        return false;
    }

    if (header.magic[0] != 'A' || header.magic[1] != 'V' ||
        header.magic[2] != 'O' || header.magic[3] != 'I') {
        return false;
    }

    // Accept any version for now (future-proof)
    return true;
}

std::shared_ptr<auraloid::Voice> AuravoiceReader::load(const std::string& path) {
    if (!validateHeader(path)) {
        return nullptr;
    }

    // NOTE:
    // Full block parsing (voice_info, phonemes, samples, models)
    // will be implemented incrementally.

    // Placeholder: return empty Voice instance once available
    return nullptr;
}

} // namespace auraloid::voice

