#pragma once

#include <vector>

#include "engine/core/audio/audio_buffer.h"

namespace auraloid {

class Mixer {
public:
    Mixer();

    // Mixa buffers mono em um buffer estéreo
    AudioBuffer<float> mixStereo(
        const std::vector<AudioBuffer<float>>& tracks,
        const std::vector<float>& volumes,
        const std::vector<float>& pans
    );

private:
    void applyPan(
        float mono,
        float pan,
        float& left,
        float& right
    );
};

}
