#include "model_block.h"
#include <stdexcept>
#include <cstring>

namespace auraloid {

// Estrutura do header do model block
struct RawModelHeader {
    uint8_t modelFormat;   // 0 = custom, 1 = ONNX
    uint32_t modelSize;    // tamanho do blob
    // logo depois vem o blob de bytes
};

NeuralModel ModelBlockParser::parse(const std::vector<uint8_t>& data) {
    if (data.size() < sizeof(RawModelHeader))
        throw std::runtime_error("MODEL_BLOCK corrupted or too small");

    RawModelHeader header;
    std::memcpy(&header, data.data(), sizeof(RawModelHeader));

    if (data.size() < sizeof(RawModelHeader) + header.modelSize)
        throw std::runtime_error("MODEL_BLOCK size mismatch");

    NeuralModel model;
    model.modelFormat = header.modelFormat;
    model.blob.resize(header.modelSize);

    std::memcpy(model.blob.data(), data.data() + sizeof(RawModelHeader), header.modelSize);

    return model;
}

}
