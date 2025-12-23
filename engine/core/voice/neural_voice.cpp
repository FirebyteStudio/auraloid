#include "neural_voice.h"

#include <cmath>
#include <iostream>

namespace auraloid {

NeuralVoice::NeuralVoice()
    : m_sampleRate(44100) {}

bool NeuralVoice::loadModel(const std::string& path) {
    // dummy: aceita qualquer coisa
    std::cout << "[NeuralVoice] Dummy model loaded: " << path << "\n";
    return true;
}

AudioBuffer<float> NeuralVoice::render(
    const RenderRequest& request
) {
    int totalFrames = static_cast<int>(
        request.duration * m_sampleRate
    );

    AudioBuffer<float> buffer(1, totalFrames);

    float freq = request.frequency;
    float velocity = request.velocity;

    float vibratoFreq = 5.0f;      // 5 Hz
    float vibratoDepth = 0.01f;    // ±1%

    for (int i = 0; i < totalFrames; ++i) {
        float t = static_cast<float>(i) / m_sampleRate;

        // vibrato
        float vib =
            std::sin(2.0f * M_PI * vibratoFreq * t)
            * vibratoDepth;

        float phase =
            2.0f * M_PI * freq * (1.0f + vib) * t;

        float sample = std::sin(phase);

        // envelope ADSR simples
        float env = 1.0f;
        float attack = 0.05f;
        float release = 0.1f;

        if (t < attack)
            env = t / attack;
        else if (t > request.duration - release)
            env = (request.duration - t) / release;

        if (env < 0.0f) env = 0.0f;

        buffer.set(
            0,
            i,
            sample * env * velocity
        );
    }

    return buffer;
}

}
