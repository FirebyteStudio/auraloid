#pragma once
#include "../audio/audio_buffer.h"
#include "../seq/auraseq.h"

namespace auraloid {

class VoiceBase {
public:
    virtual ~VoiceBase() = default;

    virtual AudioBuffer<float> synthesize(
        const SeqTrack& track,
        int sampleRate
    ) = 0;
};

}
