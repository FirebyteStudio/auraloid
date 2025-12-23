#pragma once

#include <string>
#include <memory>
#include "engine/core/audio/audio_buffer.h"

namespace auraloid {

struct RenderRequest {
    std::string phoneme;
    float frequency;
    float duration;   // segundos
    float velocity;
};

class IVoice {
public:
    virtual ~IVoice() = default;

    virtual bool isNeural() const = 0;

    virtual AudioBuffer<float> render(
        const RenderRequest& request
    ) = 0;
};

using VoicePtr = std::shared_ptr<IVoice>;

}
