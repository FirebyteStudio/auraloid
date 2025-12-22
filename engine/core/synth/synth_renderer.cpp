#include "synth_renderer.h"
#include <algorithm>
#include <iostream>

namespace auraloid {

void SynthRenderer::loadVoice(const LoadedVoice& v) {
    voice = v;
}

void SynthRenderer::loadSequence(const LoadedSequence& seq) {
    sequence = seq;
}

AudioBuffer SynthRenderer::render() {
    if (sequence.tracks.empty()) return AudioBuffer();

    uint32_t sr = 44100; // default
    size_t totalSamples = 0;

    // calcular tamanho total aproximado
    for (const auto& track : sequence.tracks) {
        for (const auto& note : track.notes) {
            totalSamples += note.length; // simplificação: length em ticks
        }
    }

    std::vector<float> finalPCM(totalSamples, 0.0f);
    AudioBuffer finalBuffer(finalPCM, sr, 1); // mono simplificado

    size_t cursor = 0;
    for (const auto& track : sequence.tracks) {
        for (const auto& note : track.notes) {
            AudioBuffer noteBuffer = renderNote(note);
            mixBuffer(finalBuffer, noteBuffer, cursor);
            cursor += noteBuffer.getPCM().size();
        }
    }

    return finalBuffer;
}

AudioBuffer SynthRenderer::renderNote(const SeqNote& note) {
    if (voice.samples.empty()) return AudioBuffer();

    // pegar primeiro sample disponível (placeholder)
    const Sample& sample = voice.samples[0];

    std::vector<float> pcm = sample.buffer.getPCM();
    applyPitchCurve(pcm, note);
    applyVelocity(pcm, note.velocity);

    return AudioBuffer(pcm, sample.buffer.getSampleRate(), sample.buffer.getChannels());
}

void SynthRenderer::applyPitchCurve(std::vector<float>& pcm, const SeqNote& note) {
    // placeholder linear pitch shift (não implementa resampling real)
    // futuro: aplicar resampling ou DSP real
}

void SynthRenderer::applyVelocity(std::vector<float>& pcm, float velocity) {
    for (auto& v : pcm) v *= velocity;
}

void SynthRenderer::mixBuffer(AudioBuffer& target, const AudioBuffer& src, size_t offset) {
    auto& tgtPCM = target.getPCM();
    const auto& srcPCM = src.getPCM();

    if (offset + srcPCM.size() > tgtPCM.size())
        tgtPCM.resize(offset + srcPCM.size(), 0.0f);

    for (size_t i = 0; i < srcPCM.size(); ++i) {
        tgtPCM[offset + i] += srcPCM[i];
    }
}

} // namespace auraloid
