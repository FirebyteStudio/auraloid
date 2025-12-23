#include "neural_voice.h"
#include "../synth/pitch_curve.h"
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
        int frameCount = note.length / 60; // v0.3: grosseiro

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
