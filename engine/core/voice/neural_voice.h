#pragma once

#include "IVoice.h"

namespace auraloid {

class NeuralVoice : public IVoice {
public:
    NeuralVoice();

    bool isNeural() const override { return true; }

    bool loadModel(const std::string& path);

    AudioBuffer<float> render(
        const RenderRequest& request
    ) override;

private:
    // placeholder por enquanto
    int m_sampleRate = 44100;
};

}
