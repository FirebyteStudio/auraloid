#include "audio_buffer.h"
#include <algorithm>

namespace auraloid {

AudioBuffer::AudioBuffer(const std::vector<float>& pcmData, uint32_t sr, uint8_t ch)
    : pcm(pcmData), sampleRate(sr), channels(ch) {}

const std::vector<float>& AudioBuffer::getPCM() const {
    return pcm;
}

uint32_t AudioBuffer::getSampleRate() const {
    return sampleRate;
}

uint8_t AudioBuffer::getChannels() const {
    return channels;
}

void AudioBuffer::mix(const AudioBuffer& other) {
    if (other.pcm.size() > pcm.size()) {
        pcm.resize(other.pcm.size(), 0.0f);
    }

    for (size_t i = 0; i < other.pcm.size(); ++i) {
        pcm[i] += other.pcm[i];
    }
}

} // namespace auraloid
