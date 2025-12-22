#include "auravoice_reader.h"

#include "blocks/voice_info.h"
#include "blocks/phoneme_block.h"
#include "blocks/sample_block.h"
#include "blocks/model_block.h"

#include <fstream>
#include <vector>
#include <cstdint>
#include <memory>

namespace auraloid {
class Voice;
}

namespace auraloid::voice {

// Auravoice file layout (simplified)
// [Header]
// [BlockHeader][BlockData]
// [BlockHeader][BlockData] ...

struct FileHeader {
    char magic[4];      // 'A','V','O','I'
    uint8_t major;
    uint8_t minor;
};

struct BlockHeader {
    char id[4];         // INFO, PHON, SAMP, MODL
    uint64_t size;      // Size of block data
};

static bool readFileHeader(std::ifstream& file, FileHeader& out) {
    file.read(reinterpret_cast<char*>(&out), sizeof(FileHeader));
    return file.good();
}

static bool readBlockHeader(std::ifstream& file, BlockHeader& out) {
    file.read(reinterpret_cast<char*>(&out), sizeof(BlockHeader));
    return file.good();
}

bool AuravoiceReader::validateHeader(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    FileHeader header{};
    if (!readFileHeader(file, header)) {
        return false;
    }

    if (header.magic[0] != 'A' || header.magic[1] != 'V' ||
        header.magic[2] != 'O' || header.magic[3] != 'I') {
        return false;
    }

    return true;
}

std::shared_ptr<auraloid::Voice> AuravoiceReader::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return nullptr;
    }

    FileHeader header{};
    if (!readFileHeader(file, header)) {
        return nullptr;
    }

    if (header.magic[0] != 'A' || header.magic[1] != 'V' ||
        header.magic[2] != 'O' || header.magic[3] != 'I') {
        return nullptr;
    }

    // Placeholder containers
    blocks::VoiceInfo voiceInfo{};
    blocks::PhonemeBlock phonemeBlock{};
    blocks::SampleBlock sampleBlock{};
    blocks::ModelBlock modelBlock{};

    // Read blocks
    while (file.good() && !file.eof()) {
        BlockHeader block{};
        if (!readBlockHeader(file, block)) {
            break;
        }

        std::streampos dataPos = file.tellg();

        if (std::strncmp(block.id, "INFO", 4) == 0) {
            // TODO: parse VoiceInfo block
        }
        else if (std::strncmp(block.id, "PHON", 4) == 0) {
            // TODO: parse PhonemeBlock
        }
        else if (std::strncmp(block.id, "SAMP", 4) == 0) {
            // TODO: parse SampleBlock
        }
        else if (std::strncmp(block.id, "MODL", 4) == 0) {
            // TODO: parse ModelBlock
        }

        // Skip block data
        file.seekg(dataPos + static_cast<std::streamoff>(block.size));
    }

    // TODO: construct Voice object using parsed blocks
    return nullptr;
}

} // namespace auraloid::voice

