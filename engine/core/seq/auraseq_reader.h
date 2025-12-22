#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace auraloid {

class AuraseqReader {
public:
    explicit AuraseqReader(const std::string& path);

    // Retorna o JSON cru do arquivo
    nlohmann::json readJson() const;

private:
    std::string filePath;
};

} // namespace auraloid
