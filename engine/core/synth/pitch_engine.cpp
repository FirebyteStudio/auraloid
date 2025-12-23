#include "pitch_engine.h"

#include <cmath>

namespace auraloid {

constexpr float VIBRATO_RATE = 5.5f;     // Hz
constexpr float VIBRATO_DEPTH = 0.35f;   // semitons
constexpr float VIBRATO_START = 0.2f;    // começa após 20% da nota

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

float PitchEngine::evaluatePitchCurve(const Note& note, float t) const {
    if (note.pitch_curve.empty())
        return 0.0f;

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
        return 0.0f;

    float dt = (t - prev->t) / (next->t - prev->t);
    return prev->v + (next->v - prev->v) * dt;
}

float PitchEngine::evaluateVibrato(const Note& note, float t) const {
    if (note.expression != "vibrato")
        return 0.0f;

    if (t < VIBRATO_START)
        return 0.0f;

    float localT = (t - VIBRATO_START) / (1.0f - VIBRATO_START);

    float phase = 2.0f * M_PI * VIBRATO_RATE * localT;
    return std::sin(phase) * VIBRATO_DEPTH;
}

float PitchEngine::evaluate(const Note& note, float t) const {
    float baseFreq = noteToFrequency(note.note);

    float curveSemitone = evaluatePitchCurve(note, t);
    float vibratoSemitone = evaluateVibrato(note, t);

    float totalSemitone = curveSemitone + vibratoSemitone;

    return baseFreq * std::pow(2.0f, totalSemitone / 12.0f);
}

}
