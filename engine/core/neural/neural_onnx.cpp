#include "neural_onnx.h"
#include <iostream>

namespace auraloid {

NeuralONNX::NeuralONNX()
    : m_env(ORT_LOGGING_LEVEL_WARNING, "Auraloid"),
      m_session(nullptr) {

    m_options.SetIntraOpNumThreads(1);
    m_options.SetGraphOptimizationLevel(
        GraphOptimizationLevel::ORT_ENABLE_BASIC
    );
}

bool NeuralONNX::load(const std::string& modelPath) {
    try {
        m_session = new Ort::Session(
            m_env,
            modelPath.c_str(),
            m_options
        );
        std::cout << "[ONNX] Model loaded\n";
        return true;
    } catch (...) {
        std::cerr << "[ONNX] Failed to load model\n";
        return false;
    }
}

std::vector<float> NeuralONNX::infer(
    const std::vector<float>& input
) {
    // ⚠️ Dummy shape por enquanto
    std::vector<int64_t> shape = {
        1, static_cast<int64_t>(input.size())
    };

    Ort::MemoryInfo memInfo =
        Ort::MemoryInfo::CreateCpu(
            OrtArenaAllocator,
            OrtMemTypeDefault
        );

    Ort::Value inputTensor =
        Ort::Value::CreateTensor<float>(
            memInfo,
            const_cast<float*>(input.data()),
            input.size(),
            shape.data(),
            shape.size()
        );

    const char* inputNames[] = {"input"};
    const char* outputNames[] = {"output"};

    auto output = m_session->Run(
        Ort::RunOptions{nullptr},
        inputNames,
        &inputTensor,
        1,
        outputNames,
        1
    );

    float* outData =
        output[0].GetTensorMutableData<float>();

    size_t outSize =
        output[0].GetTensorTypeAndShapeInfo()
        .GetElementCount();

    return std::vector<float>(outData, outData + outSize);
}

}
