#pragma once

#include <string>
#include <memory>

namespace auraloid {
    class Voice;
}

namespace auraloid::voice {

// Reader for .auravoice binary files
// Responsible only for parsing and loading voice data
class AuravoiceReader {
public:
    AuravoiceReader() = default;
    ~AuravoiceReader() = default;

    // Load a .auravoice file from disk
    // Returns nullptr on failure
    std::shared_ptr<auraloid::Voice> load(const std::string& path);

private:
    bool validateHeader(const std::string& path);
};

} // namespace auraloid::voice

