#include "neural_voice.h"
#include "../synth/pitch_curve.h"
#include "../synth/phoneme_timing.h"
#include <cmath>

namespace auraloid {

bool NeuralVoice::loadModel(
    const void* data,
    size_t size
) {
    return m_runtime.loadFromMemory(data, size);
}

AudioBuffer<float> NeuralVoice::synthesize(
    const SeqTrack& track,
    int sampleRate
) {
    // ----------------------------
    // 1️⃣ Gerar frames neurais
    // ----------------------------
    std::vector<float> neuralInput;

    for (const auto& note : track.notes) {
        // duração da nota em segundos
float noteSec =
    (note.length / static_cast<float>(m_ppq))
    * (60.0f / m_tempo);

auto segments = splitNotePhonemes(
    note.phoneme,
    noteSec,
    m_loadedVoice->phonemeBaseDurations
);

for (size_t s = 0; s < segments.size(); ++s) {
    const auto& seg = segments[s];

    int frames =
        static_cast<int>(seg.duration * 100);

    int fadeFrames =
        static_cast<int>(frames * 0.15f);

    for (int i = 0; i < frames; ++i) {

        float gain = 1.0f;

        // fade-out do fonema anterior
        if (s > 0 && i < fadeFrames) {
            gain *= crossfadeGain(
                fadeFrames - i,
                fadeFrames,
                false
            );
        }

        // fade-in do próximo fonema
        if (s + 1 < segments.size() &&
            i >= frames - fadeFrames) {

            gain *= crossfadeGain(
                i - (frames - fadeFrames),
                fadeFrames,
                true
            );
        }

        // -------- neural frame --------
        float pitch = /* pitch curve */;
        float energy = note.velocity * gain;

        uint16_t pid =
            m_loadedVoice->getPhonemeId(seg.phoneme);

        neuralInput.push_back(pid);
        neuralInput.push_back(pitch);
        neuralInput.push_back(energy);
        neuralInput.push_back(
            static_cast<float>(i) / frames
        );
    }
}

        for (int i = 0; i < frameCount; ++i) {
            float t = static_cast<float>(i) / frameCount;

            // pitch simples (Hz)
            float basePitch = noteToHz(note.note);

            // intensidade do bend (em semitons)
            constexpr float pitchRange = 2.0f;

            float curveValue =
                evalPitchCurve(note.pitchCurve, t);

            float pitchSemitone =
                curveValue * pitchRange;

            float pitch =
                basePitch * std::pow(
                    2.0f,
                    pitchSemitone / 12.0f
                );
            float energy = note.velocity;
            
            float phoneme =
                static_cast<float>(
                    m_loadedVoice->getPhonemeId(note.phoneme)
                );

            float energy = note.velocity;

            neuralInput.push_back(phoneme);
            neuralInput.push_back(pitch);
            neuralInput.push_back(energy);
            neuralInput.push_back(t);

        }
    }

    // ----------------------------
    // 2️⃣ Inferência neural
    // ----------------------------
    std::vector<float> audio =
        m_runtime.infer(neuralInput);

    // ----------------------------
    // 3️⃣ Converter para AudioBuffer
    // ----------------------------
    AudioBuffer<float> buffer(1, audio.size());

    for (size_t i = 0; i < audio.size(); ++i) {
        buffer.set(0, i, audio[i]);
    }

    return buffer;
}

}
