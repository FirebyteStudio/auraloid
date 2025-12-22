#pragma once
#include <vector>
#include <cstdint>

namespace auraloid {

class AudioBuffer {
public:
    AudioBuffer() = default;

    // Inicializa com PCM float
    AudioBuffer(const std::vector<float>& pcm, uint32_t sampleRate, uint8_t channels);

    // Getter
    const std::vector<float>& getPCM() const;
    uint32_t getSampleRate() const;
    uint8_t getChannels() const;

    // Mistura outro buffer (simples add)
    void mix(const AudioBuffer& other);

private:
    std::vector<float> pcm;
    uint32_t sampleRate = 44100;
    uint8_t channels = 1;
};

} // namespace auraloid
