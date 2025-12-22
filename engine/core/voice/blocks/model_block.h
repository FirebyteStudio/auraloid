#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace auraloid::voice::blocks {

// ModelBlock
// Optional block for neural or hybrid voice models
// Not required for sample-only voices
struct ModelBlock {
    std::string modelType;      // e.g. "neural", "hybrid"
    std::string framework;      // e.g. "onnx", "custom"

    uint32_t inputDim;          // Model input dimension
    uint32_t outputDim;         // Model output dimension

    uint64_t dataOffset;        // Byte offset of model data in file
    uint64_t dataSize;          // Size of model data in bytes

    std::vector<std::string> features; // Supported features (pitch, breath, dynamics)
};

} // namespace auraloid::voice::blocks

