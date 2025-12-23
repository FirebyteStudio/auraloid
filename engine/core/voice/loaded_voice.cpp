#include "loaded_voice.h"

namespace auraloid {

uint16_t LoadedVoice::getPhonemeId(
    const std::string& phoneme
) const {
    auto it = phonemeMap.find(phoneme);
    if (it != phonemeMap.end())
        return it->second;

    // fallback seguro
    auto fallback = phonemeMap.find("a");
    if (fallback != phonemeMap.end())
        return fallback->second;

    return 0;
}

}
