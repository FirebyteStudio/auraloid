#pragma once

#include <vector>

namespace auraloid::synth {

// Pitch point used for curves (normalized)
struct PitchPoint {
    float t; // time (0.0 – 1.0)
    float v; // pitch offset (-1.0 – 1.0)
};

// Pitch engine responsible for pitch shaping
// Does NOT generate audio, only pitch values
class PitchEngine {
public:
    PitchEngine() = default;

    // Apply pitch curve to a base frequency
    // baseFreq: fundamental frequency in Hz
    // curve: pitch bend curve
    // time: normalized time (0.0 – 1.0)
    float evaluate(float baseFreq,
                   const std::vector<PitchPoint>& curve,
                   float time) const;
};

} // namespace auraloid::synth

