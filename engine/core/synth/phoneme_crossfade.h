#pragma once
#include <vector>

namespace auraloid {

// curva simples (linear por enquanto)
inline float fadeIn(float t) {
    return t;
}

inline float fadeOut(float t) {
    return 1.0f - t;
}

// calcula ganho para frame dentro do crossfade
float crossfadeGain(
    int frameIndex,
    int totalFrames,
    bool isFadeIn
);

}
