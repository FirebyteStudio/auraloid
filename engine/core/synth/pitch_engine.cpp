#include "pitch_engine.h"
#include <cmath>
#include <stdexcept>

namespace auraloid {

static int noteIndex(char n) {
    switch (n) {
        case 'C': return 0;
        case 'D': return 2;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 7;
        case 'A': return 9;
        case 'B': return 11;
        default: return -1;
    }
}

double PitchEngine::noteToFrequency(const std::string& note) {
    if (note.size() < 2)
        throw std::runtime_error("Invalid note format");

    char base = note[0];
    int idx = noteIndex(base);
    if (idx < 0)
        throw std::runtime_error("Invalid note");

    int pos = 1;
    if (note[pos] == '#') {
        idx += 1;
        pos++;
    }

    int octave = std::stoi(note.substr(pos));

    int midiNote = (octave + 1) * 12 + idx;
    return 440.0 * std::pow(2.0, (midiNote - 69) / 12.0);
}

std::vector<float> PitchEngine::applyPitch(
    const std::vector<float>& input,
    double sourceFreq,
    double targetFreq
) {
    double ratio = targetFreq / sourceFreq;
    if (ratio <= 0.0) return input;

    size_t outSize = static_cast<size_t>(input.size() / ratio);
    std::vector<float> output(outSize);

    for (size_t i = 0; i < outSize; ++i) {
        size_t srcIndex = static_cast<size_t>(i * ratio);
        if (srcIndex < input.size())
            output[i] = input[srcIndex];
        else
            output[i] = 0.0f;
    }

    return output;
}

} // namespace auraloid
