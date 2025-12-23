#pragma once
#include "voice_base.h"
#include "../neural/neural_onnx.h"

namespace auraloid {

class NeuralVoice : public VoiceBase {
public:
    bool loadModel(const void* data, size_t size);

    AudioBuffer<float> synthesize(
        const SeqTrack& track,
        int sampleRate
    ) override;

private:
    NeuralONNX m_runtime;
};

}
