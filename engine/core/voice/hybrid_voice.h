#pragma once

#include "IVoice.h"

namespace auraloid {

class HybridVoice : public IVoice {
public:
    HybridVoice(
        VoicePtr sample,
        VoicePtr neural
    );

    bool isNeural() const override { return true; }

    AudioBuffer<float> render(
        const RenderRequest& request
    ) override;

private:
    VoicePtr m_sample;
    VoicePtr m_neural;
};

}
