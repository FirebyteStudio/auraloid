#pragma once

#include <string>
#include <vector>

#include "engine/core/seq/auraseq.h"

namespace auraloid {

class PitchEngine {
public:
    PitchEngine();

    // t: tempo normalizado da nota (0.0–1.0)
    float evaluate(const Note& note, float t) const;

private:
    float noteToFrequency(const std::string& note) const;
    float evaluatePitchCurve(const Note& note, float t) const;
    float evaluateVibrato(const Note& note, float t) const;
};

}
