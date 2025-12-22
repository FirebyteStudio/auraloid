#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace auraloid {

// =======================
// Voice basic structures
// =======================

struct VoiceRange {
    std::string min; // e.g. A2
    std::string max; // e.g. E6
};

struct VoiceInfo {
    std::string id;
    std::string name;
    std::string language;
    std::string voiceType;   // "neural" or "sample"
    std::string gender;
    VoiceRange range;
    std::string author;
    std::string engineVersion;
    std::string description;
};

// =======================
// Phoneme
// =======================

struct Phoneme {
    uint16_t id;
    std::string symbol;
    float baseDuration; // seconds
};

// =======================
// Sample (sample-based)
// =======================

struct Sample {
    uint16_t phonemeId;
    uint32_t sampleRate;
    std::vector<float> pcm; // decoded audio (mono)
};

// =======================
// Neural model (opaque)
// =======================

struct NeuralModel {
    uint8_t modelFormat; // custom / onnx
    std::vector<uint8_t> blob;
};

// =======================
// Expression
// =======================

struct Expression {
    uint8_t id;
    std::string name;
    float min;
    float max;
};

struct ExpressionSet {
    std::vector<Expression> expressions;
};

// =======================
// Final loaded voice
// =======================

struct LoadedVoice {
    VoiceInfo info;

    std::vector<Phoneme> phonemes;
    std::vector<Sample> samples;   // empty if neural
    NeuralModel model;              // empty if sample-based
    ExpressionSet expressions;

    bool isNeural = false;
};

} // namespace auraloid
