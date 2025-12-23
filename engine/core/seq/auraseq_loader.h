#pragma once

#include <string>
#include <vector>
#include <utility>

namespace auraloid {

// -------------------------
// Estruturas internas
// -------------------------

struct SeqNote {
    std::string note;   // C4, D#5
    int tick;
    int length;

    std::string lyric;
    std::string phoneme;

    float velocity = 1.0f;
    std::string expression;

    // time(normalized 0–1), value(semitones)
    std::vector<std::pair<float, float>> pitchCurve;
};

struct SeqTrack {
    std::string id;
    std::string name;

    std::string voice;   // LoadedVoice id
    float volume = 1.0f;
    float pan = 0.0f;    // -1 left, +1 right

    std::vector<SeqNote> notes;
};

struct LoadedSequence {
    int ppq = 480;
    float tempo = 120.0f;
    std::string timeSignature = "4/4";

    std::vector<SeqTrack> tracks;
};

// -------------------------
// Loader
// -------------------------

class AuraseqLoader {
public:
    static LoadedSequence load(const std::string& path);
};

} // namespace auraloid
