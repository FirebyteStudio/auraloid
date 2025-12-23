#pragma once
#include <vector>
#include <utility>

namespace auraloid {

// pitchCurve = vector< {t, v} >
float evalPitchCurve(
    const std::vector<std::pair<float,float>>& pitchCurve,
    float t
);

}
