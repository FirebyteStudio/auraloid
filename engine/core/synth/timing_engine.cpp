#include "timing_engine.h"

namespace auraloid {

TimingEngine::TimingEngine(int p, float t, uint32_t sr)
    : ppq(p), tempo(t), sampleRate(sr) {}

double TimingEngine::ticksToSeconds(int ticks) const {
    // BPM → seconds per beat
    double secPerBeat = 60.0 / tempo;
    double beats = static_cast<double>(ticks) / ppq;
    return beats * secPerBeat;
}

uint64_t TimingEngine::ticksToSamples(int ticks) const {
    return static_cast<uint64_t>(ticksToSeconds(ticks) * sampleRate);
}

uint64_t TimingEngine::noteLengthSamples(const SeqNote& note) const {
    return ticksToSamples(note.length);
}

} // namespace auraloid
