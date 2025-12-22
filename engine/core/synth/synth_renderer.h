#pragma once
#include "../voice/loaded_voice.h"
#include "../seq/auraseq_loader.h"
#include "../audio/audio_buffer.h"
#include <vector>

namespace auraloid {

class SynthRenderer {
public:
    SynthRenderer() = default;

    void loadVoice(const LoadedVoice& voice);
    void loadSequence(const LoadedSequence& seq);

    // Renderiza a sequência completa em um AudioBuffer
    AudioBuffer render();

private:
    LoadedVoice voice;
    LoadedSequence sequence;

    // Renderiza uma nota para um buffer
    AudioBuffer renderNote(const SeqNote& note);

    // Aplica pitch curve simples (linear)
    void applyPitchCurve(std::vector<float>& pcm, const SeqNote& note);

    // Aplica velocity
    void applyVelocity(std::vector<float>& pcm, float velocity);

    // Mixa dois buffers
    void mixBuffer(AudioBuffer& target, const AudioBuffer& src, size_t offset);
};

} // namespace auraloid
