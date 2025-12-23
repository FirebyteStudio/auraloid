#pragma once
#include "../seq/auraseq_loader.h"
#include <cstdint>

namespace auraloid {

class TimingEngine {
public:
    TimingEngine(int ppq, float tempo, uint32_t sampleRate);

    // ticks → segundos
    double ticksToSeconds(int ticks) const;

    // ticks → samples
    uint64_t ticksToSamples(int ticks) const;

    // duração real de uma nota em samples
    uint64_t noteLengthSamples(const SeqNote& note) const;

private:
    int ppq;
    float tempo;
    uint32_t sampleRate;
};

} // namespace auraloid
