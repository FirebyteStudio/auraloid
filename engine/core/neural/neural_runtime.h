#pragma once
#include <vector>

namespace auraloid {

struct NeuralFrameInput {
    float phoneme_id;
    float pitch;
    float energy;
    float time;
};

class NeuralRuntime {
public:
    virtual ~NeuralRuntime() = default;

    virtual bool loadModel(const void* data, size_t size) = 0;

    virtual std::vector<float> infer(
        const std::vector<NeuralFrameInput>& frames
    ) = 0;
};

}
