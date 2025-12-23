#include "neural_runtime.h"
#include <onnxruntime_cxx_api.h>

namespace auraloid {

class NeuralONNXRuntime : public NeuralRuntime {
    Ort::Env env{ORT_LOGGING_LEVEL_WARNING, "auraloid"};
    Ort::Session* session = nullptr;

public:
    bool loadModel(const void* data, size_t size) override {
        Ort::SessionOptions opts;
        opts.SetIntraOpNumThreads(1);

        session = new Ort::Session(
            env,
            data,
            size,
            opts
        );
        return true;
    }

    std::vector<float> infer(
        const std::vector<NeuralFrameInput>& frames
    ) override {
        // v0.3: dummy real
        std::vector<float> audio(frames.size() * 256);
        return audio;
    }
};

}
