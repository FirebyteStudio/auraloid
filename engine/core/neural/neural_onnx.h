#pragma once

#include <onnxruntime_cxx_api.h>
#include <string>
#include <vector>

namespace auraloid {

class NeuralONNX {
public:
    NeuralONNX();
    bool load(const std::string& modelPath);

    std::vector<float> infer(
        const std::vector<float>& input
    );

private:
    Ort::Env m_env;
    Ort::Session* m_session;
    Ort::SessionOptions m_options;
};

}
