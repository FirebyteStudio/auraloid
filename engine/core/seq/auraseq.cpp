#include "auraseq.h"
#include <cmath>

namespace auraloid {

// util simples: nota → frequência
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

static float noteToFrequency(const std::string& note) {
    if (note.size() < 2) return 440.0f;

    char n = note[0];
    int octave = note.back() - '0';
    int semitone = noteIndex(n);

    if (note.size() >= 3 && note[1] == '#')
        semitone += 1;

    int midi = (octave + 1) * 12 + semitone;
    return 440.0f * std::pow(2.0f, (midi - 69) / 12.0f);
}

// opcional: preparar runtime data
void prepareSequence(AuraSeq& seq) {
    for (auto& track : seq.tracks) {
        for (auto& note : track.notes) {
            note.frequency = noteToFrequency(note.note);

            // phoneme_id provisório (hash simples)
            float h = 0.0f;
            for (char c : note.phoneme)
                h += static_cast<float>(c);

            note.phoneme_id = std::fmod(h, 40.0f) / 40.0f;
        }
    }
}

}
