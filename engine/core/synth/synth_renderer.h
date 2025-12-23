#pragma once

#include <vector>
#include <memory>

#include "../audio/audio_buffer.h"
#include "../voice/loaded_voice.h"
#include "../seq/auraseq.h"
#include "../synth/pitch_engine.h"


namespace auraloid {

class SynthRenderer {
public:
    SynthRenderer();

    void setVoice(std::shared_ptr<LoadedVoice> voice);
    void setSequence(const AuraSeq& sequence);

    AudioBuffer<float> render();

private:
    std::shared_ptr<LoadedVoice> m_voice;
    AuraSeq m_sequence;

    float noteToFrequency(const std::string& note) const;
};

}
