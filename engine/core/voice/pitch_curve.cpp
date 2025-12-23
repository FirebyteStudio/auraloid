#include "pitch_curve.h"

namespace auraloid {

float evalPitchCurve(
    const std::vector<std::pair<float,float>>& curve,
    float t
) {
    if (curve.empty())
        return 0.0f;

    if (t <= curve.front().first)
        return curve.front().second;

    if (t >= curve.back().first)
        return curve.back().second;

    for (size_t i = 0; i + 1 < curve.size(); ++i) {
        auto [t0, v0] = curve[i];
        auto [t1, v1] = curve[i + 1];

        if (t >= t0 && t <= t1) {
            float k = (t - t0) / (t1 - t0);
            return v0 + k * (v1 - v0);
        }
    }

    return 0.0f;
}

}
