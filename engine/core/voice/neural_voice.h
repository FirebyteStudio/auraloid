#pragma once

#include "IVoice.h"

namespace auraloid {

class NeuralVoice : public IVoice {
public:
    NeuralVoice();

    bool isNeural() const override { return true; }

    // no futuro: carrega ONNX / modelo neural
    bool loadModel(const std::string& path);

    AudioBuffer<float> render(
        const RenderRequest& request
    ) override;

private:
    int m_sampleRate;
};

}
