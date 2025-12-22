#pragma once

#include <memory>
#include <string>

#include "pitch_engine.h"
#include "timing_engine.h"

namespace auraloid {
    class Voice;
    class Sequence;
}

namespace auraloid::audio {
    class AudioBuffer;
}

namespace auraloid::synth {

// Main synthesis renderer
// Orchestrates timing, pitch and audio generation
class Renderer {
public:
    Renderer();
    ~Renderer();

    // Non-copyable
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    // Render a sequence using a given voice
    bool render(
        const Sequence& sequence,
        const Voice& voice,
        audio::AudioBuffer& output
    );

private:
    PitchEngine pitchEngine_;
    TimingEngine timingEngine_;
};

} // namespace auraloid::synth

