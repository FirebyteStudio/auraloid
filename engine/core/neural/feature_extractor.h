#pragma once

#include <vector>
#include <string>

#include "../seq/auraseq.h"

namespace auraloid {

struct NeuralFeatures {
    int frames;
    int features;
    std::vector<float> data; // flat [T * F]
};

class FeatureExtractor {
public:
    FeatureExtractor(int sampleRate = 44100, int hopSize = 256);

    NeuralFeatures extract(
        const AuraSeq& seq,
        int trackIndex = 0
    );

private:
    int m_sampleRate;
    int m_hopSize;

    float normalizePitch(float hz) const;
};

}
