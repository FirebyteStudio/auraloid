#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace auraloid::voice::blocks {

// Represents a single audio sample entry inside a voicebank
// Audio data itself is stored as FLAC inside the .auravoice container
struct SampleEntry {
    std::string id;          // Unique sample identifier
    std::string phoneme;     // Associated phoneme (e.g. "a", "k", "sil")

    uint32_t sampleRate;     // Sample rate of this sample
    uint16_t channels;       // Channel count

    uint64_t dataOffset;     // Byte offset inside .auravoice file
    uint64_t dataSize;       // Size of FLAC data in bytes
};

// SampleBlock
// Contains all sample references used by the voice
struct SampleBlock {
    std::vector<SampleEntry> samples;
};

} // namespace auraloid::voice::blocks

