#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "../loaded_voice.h"

namespace auraloid {

class VoiceInfoParser {
public:
    // Parse a JSON string into a VoiceInfo struct
    static VoiceInfo parse(const std::string& jsonStr);
};

}
