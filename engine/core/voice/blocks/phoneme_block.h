
#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace auraloid::voice::blocks {

// Represents a single phoneme definition
struct Phoneme {
    std::string symbol;      // Phoneme symbol (e.g. "a", "ka", "N")
    std::string alias;       // Optional alias / fallback

    float defaultDuration;   // Default duration in seconds
    float minDuration;       // Minimum allowed duration
    float maxDuration;       // Maximum allowed duration

    bool vowel;              // True if vowel
    bool consonant;          // True if consonant
};

// PhonemeBlock
// Defines the phoneme inventory and timing rules of the voice
struct PhonemeBlock {
    std::vector<Phoneme> phonemes;
};

} // namespace auraloid::voice::blocks
