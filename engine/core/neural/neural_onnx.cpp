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

bool NeuralONNX::loadFromMemory(
    const void* data,
    size_t size
) {
    try {
        m_session = new Ort::Session(
            m_env,
            data,
            size,
            m_options
        );

        std::cout << "[ONNX] Neural model loaded from memory\n";
        return true;

    } catch (const Ort::Exception& e) {
        std::cerr << "[ONNX] Load failed: "
                  << e.what() << "\n";
        return false;
    }
}

std::vector<float> NeuralONNX::infer(
    const std::vector<float>& input
) {
    if (!m_session) {
        std::cerr << "[ONNX] Session not initialized\n";
        return {};
    }

    // ⚠️ v0.3 — shape simples (batch=1)
    std::vector<int64_t> shape = {
        1,
        static_cast<int64_t>(input.size())
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

    const char* inputNames[]  = {"input"};
    const char* outputNames[] = {"output"};

    auto outputTensors = m_session->Run(
        Ort::RunOptions{nullptr},
        inputNames,
        &inputTensor,
        1,
        outputNames,
        1
    );

    float* outData =
        outputTensors[0]
        .GetTensorMutableData<float>();

    size_t outSize =
        outputTensors[0]
        .GetTensorTypeAndShapeInfo()
        .GetElementCount();

    return std::vector<float>(outData, outData + outSize);
}

}
