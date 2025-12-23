#pragma once
#include <vector>
#include <cstddef>
#include <onnxruntime_cxx_api.h>

namespace auraloid {

class NeuralONNX {
public:
    NeuralONNX();

    bool loadFromMemory(const void* data, size_t size);

    std::vector<float> infer(
        const std::vector<float>& input
    );

private:
    Ort::Env m_env;
    Ort::SessionOptions m_options;
    Ort::Session* m_session;
};

}
