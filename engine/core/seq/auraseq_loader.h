#pragma once
#include <string>
#include <vector>
#include "auraseq_reader.h"
#include "../../voice/loaded_voice.h"

namespace auraloid {

// -------------------------
// Estruturas internas
// -------------------------
struct SeqNote {
    std::string note;
    int tick;
    int length;
    std::string lyric;
    std::string phoneme;
    float velocity;
    std::string expression;
    std::vector<std::pair<float,float>> pitchCurve;
};

struct SeqTrack {
    std::string id;
    std::string name;
    std::string voice;  // LoadedVoice id
    float volume;
    float pan;
    std::vector<SeqNote> notes;
};

struct LoadedSequence {
    int ppq;
    float tempo;
    std::string timeSignature;
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
