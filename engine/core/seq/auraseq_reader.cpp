#include "auraseq_reader.h"
#include <fstream>
#include <stdexcept>

namespace auraloid {

AuraseqReader::AuraseqReader(const std::string& path)
    : filePath(path) {}

nlohmann::json AuraseqReader::readJson() const {
    std::ifstream in(filePath);
    if (!in.is_open())
        throw std::runtime_error("Failed to open .auraseq file: " + filePath);

    nlohmann::json j;
    in >> j;
    return j;
}

} // namespace auraloid
