#include "pitch_engine.h"

#include <cmath>

namespace auraloid {

PitchEngine::PitchEngine() {}

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

float PitchEngine::noteToFrequency(const std::string& note) const {
    if (note.size() < 2) return 440.0f;

    char n = note[0];
    int octave = note.back() - '0';
    int semitone = noteIndex(n);

    if (note.size() == 3 && note[1] == '#')
        semitone++;

    int midi = (octave + 1) * 12 + semitone;
    return 440.0f * std::pow(2.0f, (midi - 69) / 12.0f);
}

float PitchEngine::evaluate(const Note& note, float t) const {
    float baseFreq = noteToFrequency(note.note);

    if (note.pitch_curve.empty())
        return baseFreq;

    // Clamp t
    if (t <= 0.0f) return baseFreq;
    if (t >= 1.0f) t = 1.0f;

    const PitchPoint* prev = nullptr;
    const PitchPoint* next = nullptr;

    for (size_t i = 0; i < note.pitch_curve.size(); ++i) {
        if (note.pitch_curve[i].t >= t) {
            next = &note.pitch_curve[i];
            if (i > 0) prev = &note.pitch_curve[i - 1];
            break;
        }
    }

    if (!prev || !next)
        return baseFreq;

    float dt = (t - prev->t) / (next->t - prev->t);
    float bend = prev->v + (next->v - prev->v) * dt;

    // v ∈ [-1,1] → semitones (-1 = -1st, +1 = +1st)
    float semitoneOffset = bend;
    return baseFreq * std::pow(2.0f, semitoneOffset / 12.0f);
}

}


    return output;
}

} // namespace auraloid
