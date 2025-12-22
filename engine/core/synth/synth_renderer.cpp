#include "synth_renderer.h"
#include <iostream>

namespace auraloid {

void SynthRenderer::loadVoice(const LoadedVoice& v) {
    voice = v;
}

void SynthRenderer::loadSequence(const LoadedSequence& seq) {
    sequence = seq;
}

void SynthRenderer::playSample(const Sample& sample) {
    // Placeholder: aqui você integraria com a API de áudio real
    std::cout << "Playing sample for phoneme ID: " << sample.phonemeId
              << ", PCM size: " << sample.pcm.size() << "\n";
}

void SynthRenderer::playTestNote() {
    if (voice.samples.empty()) {
        std::cerr << "No samples available for this voice.\n";
        return;
    }

    if (sequence.tracks.empty() || sequence.tracks[0].notes.empty()) {
        std::cerr << "No notes in sequence.\n";
        return;
    }

    const auto& note = sequence.tracks[0].notes[0];
    std::cout << "Playing test note: " << note.note
              << ", lyric: " << note.lyric
              << ", phoneme: " << note.phoneme << "\n";

    // Encontrar o sample correspondente ao phoneme
    auto it = std::find_if(voice.samples.begin(), voice.samples.end(),
                           [&](const Sample& s){ return s.phonemeId == 0; }); // placeholder ID

    if (it != voice.samples.end()) {
        playSample(*it);
    } else {
        std::cerr << "Sample for phoneme not found, playing first sample.\n";
        playSample(voice.samples[0]);
    }
}

} // namespace auraloid
