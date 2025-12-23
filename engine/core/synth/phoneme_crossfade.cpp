#include "phoneme_crossfade.h"

namespace auraloid {

float crossfadeGain(
    int frameIndex,
    int totalFrames,
    bool isFadeIn
) {
    if (totalFrames <= 0)
        return 1.0f;

    float t =
        static_cast<float>(frameIndex) /
        static_cast<float>(totalFrames);

    return isFadeIn ? fadeIn(t) : fadeOut(t);
}

}
