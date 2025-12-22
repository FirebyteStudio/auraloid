#include "voice_info.h"
#include <stdexcept>

namespace auraloid {

VoiceInfo VoiceInfoParser::parse(const std::string& jsonStr) {
    VoiceInfo info;

    try {
        auto j = nlohmann::json::parse(jsonStr);

        info.id            = j.at("id").get<std::string>();
        info.name          = j.at("name").get<std::string>();
        info.language      = j.at("language").get<std::string>();
        info.voiceType     = j.at("voice_type").get<std::string>();
        info.gender        = j.at("gender").get<std::string>();
        info.range.min     = j.at("range").at("min").get<std::string>();
        info.range.max     = j.at("range").at("max").get<std::string>();
        info.author        = j.at("author").get<std::string>();
        info.engineVersion = j.at("engine_version").get<std::string>();
        info.description   = j.at("description").get<std::string>();
    }
    catch (std::exception& e) {
        throw std::runtime_error("Failed to parse VoiceInfo JSON: " + std::string(e.what()));
    }

    return info;
}

}
