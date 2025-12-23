#include "feature_extractor.h"
#include <cmath>
#include <algorithm>

namespace auraloid {

FeatureExtractor::FeatureExtractor(int sampleRate, int hopSize)
    : m_sampleRate(sampleRate), m_hopSize(hopSize) {}

float FeatureExtractor::normalizePitch(float hz) const {
    if (hz <= 0.0f) return 0.0f;

    float p = std::log2(hz);
    float min = std::log2(55.0f);
    float max = std::log2(1760.0f);

    return std::clamp((p - min) / (max - min), 0.0f, 1.0f);
}

NeuralFeatures FeatureExtractor::extract(
    const AuraSeq& seq,
    int trackIndex
) {
    NeuralFeatures nf;
    nf.features = 8;

    if (seq.tracks.empty())
        return nf;

    const auto& track = seq.tracks[trackIndex];

    float secondsPerTick =
        60.0f / (seq.tempo * seq.ppq);

    float totalTime = 0.0f;
    for (const auto& n : track.notes) {
        float end =
            (n.tick + n.length) * secondsPerTick;
        totalTime = std::max(totalTime, end);
    }

    nf.frames =
        static_cast<int>(
            totalTime * m_sampleRate / m_hopSize
        );

    nf.data.resize(nf.frames * nf.features, 0.0f);

    for (const auto& note : track.notes) {
        float startSec = n.tick * secondsPerTick;
        float endSec =
            (n.tick + n.length) * secondsPerTick;

        int startFrame =
            static_cast<int>(startSec * m_sampleRate / m_hopSize);
        int endFrame =
            static_cast<int>(endSec * m_sampleRate / m_hopSize);

        float pitchNorm =
            normalizePitch(note.frequency);

        for (int f = startFrame; f < endFrame; ++f) {
            int base = f * nf.features;

            nf.data[base + 0] = note.phoneme_id;
            nf.data[base + 1] = pitchNorm;
            nf.data[base + 2] = note.velocity;
            nf.data[base + 3] = note.breath;
            nf.data[base + 4] = note.expression;
            nf.data[base + 5] = note.vibrato;
            nf.data[base + 6] = (f == startFrame) ? 1.0f : 0.0f;
            nf.data[base + 7] = (f == endFrame - 1) ? 1.0f : 0.0f;
        }
    }

    return nf;
}

}
