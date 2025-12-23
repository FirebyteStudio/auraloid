#include "synth_renderer.h"

#include <cmath>
#include <iostream>

#include "engine/core/synth/pitch_engine.h"
#include "engine/core/synth/timing_engine.h"

namespace auraloid {

constexpr float CROSSFADE_RATIO = 0.15f;
constexpr int SAMPLE_RATE = 44100;

SynthRenderer::SynthRenderer() {}

void SynthRenderer::setVoice(std::shared_ptr<LoadedVoice> voice) {
    m_voice = voice;
}

void SynthRenderer::setSequence(const AuraSeq& sequence) {
    m_sequence = sequence;
}

AudioBuffer<float> SynthRenderer::render() {
    AudioBuffer<float> output(1, SAMPLE_RATE * 60); // 1 min max
    size_t writeCursor = 0;

    if (!m_voice) {
        std::cerr << "[SynthRenderer] No voice loaded\n";
        return {};
    }

    if (m_sequence.tracks.empty()) {
        std::cerr << "[SynthRenderer] No tracks\n";
        return {};
    }

    const auto& track = m_sequence.tracks[0];

    PitchEngine pitchEngine;
    TimingEngine timingEngine;

    for (const auto& note : track.notes) {

        // duração da nota em segundos
        float noteDurationSec =
            (note.length / (float)m_sequence.ppq) *
            (60.0f / m_sequence.tempo);

        // gerar eventos fonêmicos
        auto phonemes = timingEngine.generate(
            note,
            *m_voice,
            noteDurationSec
        );

        for (size_t p = 0; p < phonemes.size(); ++p) {
            const auto& ph = phonemes[p];

            auto sample = m_voice->getSample(ph.phoneme);
            if (!sample) continue;

            const auto& src = sample->audio;

            size_t phonemeFrames =
                static_cast<size_t>(ph.length * SAMPLE_RATE);

            size_t fadeFrames =
                static_cast<size_t>(phonemeFrames * CROSSFADE_RATIO);

            for (size_t i = 0; i < phonemeFrames; ++i) {
                if (writeCursor >= output.frames()) break;
                if (i >= src.frames()) break;

                // tempo normalizado dentro da nota
                float noteT =
                    (ph.start + (i / (float)SAMPLE_RATE)) /
                    noteDurationSec;

                // frequência com pitch curve
                float freq = pitchEngine.evaluate(note, noteT);
                float ratio = freq / sample->baseFrequency;

                size_t srcIndex =
                    static_cast<size_t>(i * ratio);

                if (srcIndex >= src.frames()) break;

                float gain = 1.0f;

                // fade-in
                if (p > 0 && i < fadeFrames) {
                    gain *= (float)i / fadeFrames;
                }

                // fade-out
                if (p + 1 < phonemes.size() &&
                    i >= phonemeFrames - fadeFrames) {
                    float x =
                        (phonemeFrames - i) /
                        (float)fadeFrames;
                    gain *= x;
                }

                float s = src.get(0, srcIndex);
                output.set(
                    0,
                    writeCursor++,
                    s * gain * note.velocity
                );
            }
        }
    }

    output.resize(writeCursor);
    return output;
}

}
