#pragma once
#include "../voice/loaded_voice.h"
#include "../seq/auraseq_loader.h"

namespace auraloid {

class SynthRenderer {
public:
    SynthRenderer() = default;

    // Carrega voice e sequence
    void loadVoice(const LoadedVoice& voice);
    void loadSequence(const LoadedSequence& seq);

    // Toca a primeira nota de teste (sample-based)
    void playTestNote();

private:
    LoadedVoice voice;
    LoadedSequence sequence;

    // Função auxiliar para tocar sample (placeholder)
    void playSample(const Sample& sample);
};

} // namespace auraloid
