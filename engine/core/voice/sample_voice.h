#pragma once

#include "IVoice.h"
#include "engine/core/voice/loaded_voice.h"

namespace auraloid {

class SampleVoice : public IVoice {
public:
    SampleVoice(std::shared_ptr<LoadedVoice> voice);

    bool isNeural() const override { return false; }

    AudioBuffer<float> render(
        const RenderRequest& request
    ) override;

private:
    std::shared_ptr<LoadedVoice> m_voice;
};

}
