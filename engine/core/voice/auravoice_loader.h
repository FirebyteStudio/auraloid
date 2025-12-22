#pragma once
#include <string>
#include "auravoice_reader.h"

namespace auraloid {

struct LoadedVoice;

class AuravoiceLoader {
public:
    static LoadedVoice loadFromFile(const std::string& path);

private:
    static void validateHeader(const AuravoiceHeader& header);
};

}
