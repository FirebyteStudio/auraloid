#pragma once

#include <string>
#include <cstdint>

namespace auraloid::voice::blocks {

// VoiceInfo block
// Contains general metadata about the voicebank
struct VoiceInfo {
    std::string name;        // Display name
    std::string author;      // Voice provider
    std::string language;    // Language / phoneme set
    std::string description;// Optional description

    uint32_t sampleRate;     // Native sample rate (Hz)
    uint16_t channels;       // Channel count (usually 1)

    uint8_t versionMajor;    // Voice format major
    uint8_t versionMinor;    // Voice format minor
};

} // namespace auraloid::voice::blocks

