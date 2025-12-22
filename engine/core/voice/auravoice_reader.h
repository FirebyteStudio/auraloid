#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "block_types.h"
#include "auravoice_structs.h"

namespace auraloid {

class AuravoiceReader {
public:
    explicit AuravoiceReader(const std::string& path);
    ~AuravoiceReader();

    const AuravoiceHeader& header() const;
    const std::vector<BlockHeader>& blocks() const;

    // Low-level block access
    void readBlockData(const BlockHeader& block, std::vector<uint8_t>& out) const;

private:
    std::ifstream file;
    AuravoiceHeader fileHeader;
    std::vector<BlockHeader> blockTable;

    void readHeader();
    void scanBlocks();
};

}
