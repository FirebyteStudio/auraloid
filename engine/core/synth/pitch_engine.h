#pragma once
#include <string>
#include <vector>

namespace auraloid {

class PitchEngine {
public:
    // "C4" → Hz
    static double noteToFrequency(const std::string& note);

    // Aplica pitch estático via resampling
    static std::vector<float> applyPitch(
        const std::vector<float>& input,
        double sourceFreq,
        double targetFreq
    );
};

} // namespace auraloid
