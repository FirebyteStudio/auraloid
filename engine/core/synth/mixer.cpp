#include "mixer.h"

#include <algorithm>
#include <cmath>

namespace auraloid {

Mixer::Mixer() {}

void Mixer::applyPan(
    float mono,
    float pan,
    float& left,
    float& right
) {
    // pan: -1 = left, 0 = center, +1 = right
    float angle = (pan + 1.0f) * 0.25f * M_PI;
    left = mono * std::cos(angle);
    right = mono * std::sin(angle);
}

AudioBuffer<float> Mixer::mixStereo(
    const std::vector<AudioBuffer<float>>& tracks,
    const std::vector<float>& volumes,
    const std::vector<float>& pans
) {
    if (tracks.empty())
        return {};

    size_t maxFrames = 0;
    for (const auto& t : tracks)
        maxFrames = std::max(maxFrames, t.frames());

    AudioBuffer<float> out(2, maxFrames);

    for (size_t i = 0; i < tracks.size(); ++i) {
        const auto& track = tracks[i];
        float vol = volumes[i];
        float pan = pans[i];

        for (size_t f = 0; f < track.frames(); ++f) {
            float mono = track.get(0, f) * vol;

            float l, r;
            applyPan(mono, pan, l, r);

            out.add(0, f, l);
            out.add(1, f, r);
        }
    }

    // soft clip
    for (size_t c = 0; c < 2; ++c) {
        for (size_t f = 0; f < out.frames(); ++f) {
            float s = out.get(c, f);
            out.set(c, f, std::tanh(s));
        }
    }

    return out;
}

}
