#pragma once

#include <string>
#include <vector>

namespace auraloid {

// =========================
// Pitch curve point
// =========================
struct PitchPoint {
    float t;   // 0.0 – 1.0
    float v;   // -1.0 – 1.0
};

// =========================
// Note
// =========================
struct AuraNote {
    std::string note;      // "C4", "D#5"
    int tick;              // start tick
    int length;            // duration in ticks
    std::string lyric;
    std::string phoneme;

    float velocity = 1.0f;
    float expression = 0.5f;
    float breath = 0.0f;
    float vibrato = 0.0f;

    std::vector<PitchPoint> pitch_curve;

    // runtime helpers
    float frequency = 0.0f;
    float phoneme_id = 0.0f;
};

// =========================
// Track
// =========================
struct AuraTrack {
    std::string id;
    std::string name;
    std::string voice;

    float volume = 1.0f;
    float pan = 0.0f;

    std::vector<AuraNote> notes;
};

// =========================
// Sequence
// =========================
struct AuraSeq {
    std::string format = "auraseq";
    std::string version = "1.0";

    int ppq = 480;
    float tempo = 120.0f;
    std::string time_signature = "4/4";

    std::vector<AuraTrack> tracks;
};

}
