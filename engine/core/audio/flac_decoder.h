#pragma once
#include "audio_buffer.h"
#include <vector>
#include <cstdint>

namespace auraloid {

class FlacDecoder {
public:
    // Recebe bytes FLAC e retorna AudioBuffer
    static AudioBuffer decodeToBuffer(const std::vector<uint8_t>& flacData);
};

} // namespace auraloid
