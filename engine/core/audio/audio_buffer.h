#pragma once

#include <vector>
#include <cstddef>

namespace auraloid::audio {

// Basic PCM audio buffer (engine-internal)
// All samples are stored as 32-bit floating point
// Range: -1.0f to 1.0f
class AudioBuffer {
public:
    AudioBuffer() = default;

    AudioBuffer(std::size_t channels, std::size_t sampleRate)
        : channels_(channels), sampleRate_(sampleRate) {}

    void resize(std::size_t frames) {
        data_.resize(frames * channels_);
    }

    float* data() { return data_.data(); }
    const float* data() const { return data_.data(); }

    std::size_t frames() const {
        if (channels_ == 0) return 0;
        return data_.size() / channels_;
    }

    std::size_t channels() const { return channels_; }
    std::size_t sampleRate() const { return sampleRate_; }

    void clear() {
        std::fill(data_.begin(), data_.end(), 0.0f);
    }

private:
    std::vector<float> data_;
    std::size_t channels_ = 0;
    std::size_t sampleRate_ = 44100;
};

} // namespace auraloid::audio

