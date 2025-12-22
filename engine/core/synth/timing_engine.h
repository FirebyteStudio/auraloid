#pragma once

#include <vector>
#include <string>

namespace auraloid::synth {

// Represents a resolved phoneme timing unit
struct PhonemeTiming {
    std::string phoneme;
    float start;   // start time in seconds
    float length;  // duration in seconds
};

// Timing engine responsible for note-to-phoneme alignment
// Does NOT handle pitch or audio rendering
class TimingEngine {
public:
    TimingEngine() = default;

    // Resolve phoneme timings for a note
    // noteDuration: duration of the note in seconds
    // phonemes: ordered phoneme list
    std::vector<PhonemeTiming> resolve(
        float noteDuration,
        const std::vector<std::string>& phonemes
    ) const;
};

} // namespace auraloid::synth

