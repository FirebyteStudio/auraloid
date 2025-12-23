#include "synth_renderer.h"

#include <cmath>
#include <iostream>

namespace auraloid {

SynthRenderer::SynthRenderer() {}

void SynthRenderer::setVoice(std::shared_ptr<LoadedVoice> voice) {
    m_voice = voice;
}

void SynthRenderer::setSequence(const AuraSeq& sequence) {
    m_sequence = sequence;
}

PitchEngine pitch;
float freq = pitch.evaluate(note, noteTimeNormalized);


static int noteIndex(char n) {
    switch (n) {
        case 'C': return 0;
        case 'D': return 2;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 7;
        case 'A': return 9;
        case 'B': return 11;
    }
    return 0;
}

float SynthRenderer::noteToFrequency(const std::string& note) const {
    // Example: C4, D#5
    if (note.size() < 2) return 440.0f;

    char n = note[0];
    int octave = note.back() - '0';
    int semitone = noteIndex(n);

    if (note.size() == 3 && note[1] == '#')
        semitone += 1;

    int midi = (octave + 1) * 12 + semitone;
    return 440.0f * std::pow(2.0f, (midi - 69) / 12.0f);
}

AudioBuffer<float> SynthRenderer::render() {
    AudioBuffer<float> output(1, 44100 * 60); // 1 min max
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

    for (const auto& note : track.notes) {
        float freq = noteToFrequency(note.note);

        auto sample = m_voice->getSample(note.phoneme);
        if (!sample) continue;

        const auto& src = sample->audio;
        float ratio = freq / sample->baseFrequency;

        for (size_t i = 0; i < src.frames(); ++i) {
            size_t srcIndex = static_cast<size_t>(i * ratio);
            if (srcIndex >= src.frames()) break;

            if (writeCursor >= output.frames()) break;

            float s = src.get(0, srcIndex);
            output.set(0, writeCursor++, s * note.velocity);
        }
    }

    output.resize(writeCursor);
    return output;
}

}
