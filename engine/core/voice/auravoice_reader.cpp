#include "auravoice_reader.h"
#include <stdexcept>
#include <cstring>

namespace auraloid {

AuravoiceReader::AuravoiceReader(const std::string& path) {
    file.open(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("Failed to open .auravoice file");

    readHeader();
    scanBlocks();
}

AuravoiceReader::~AuravoiceReader() {
    if (file.is_open())
        file.close();
}

const AuravoiceHeader& AuravoiceReader::header() const {
    return fileHeader;
}

const std::vector<BlockHeader>& AuravoiceReader::blocks() const {
    return blockTable;
}

void AuravoiceReader::readHeader() {
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(AuravoiceHeader));

    if (std::strncmp(fileHeader.magic, "AURA", 4) != 0)
        throw std::runtime_error("Invalid Auraloid file (bad magic)");

    if (fileHeader.header_size < sizeof(AuravoiceHeader))
        throw std::runtime_error("Invalid header size");
}

void AuravoiceReader::scanBlocks() {
    file.seekg(fileHeader.header_size, std::ios::beg);

    while (file && !file.eof()) {
        uint32_t typeRaw;
        uint32_t size;

        file.read(reinterpret_cast<char*>(&typeRaw), sizeof(uint32_t));
        file.read(reinterpret_cast<char*>(&size), sizeof(uint32_t));

        if (file.fail())
            break;

        BlockHeader block;
        block.type = static_cast<BlockType>(typeRaw);
        block.size = size;
        block.offset = static_cast<uint32_t>(file.tellg());

        blockTable.push_back(block);

        // Skip block payload
        file.seekg(size, std::ios::cur);
    }
}

void AuravoiceReader::readBlockData(const BlockHeader& block,
                                   std::vector<uint8_t>& out) const {
    out.resize(block.size);

    file.seekg(block.offset, std::ios::beg);
    file.read(reinterpret_cast<char*>(out.data()), block.size);
}

}
