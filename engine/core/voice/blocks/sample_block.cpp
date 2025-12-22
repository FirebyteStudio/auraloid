#include "sample_block.h"
#include "../audio/flac_decoder.h" // nosso decodificador FLAC
#include <stdexcept>
#include <cstring>

namespace auraloid {

struct RawSampleEntry {
    uint16_t phonemeId;
    uint32_t offset;      // offset dentro do bloco
    uint32_t size;        // tamanho em bytes do FLAC
};

// O parser vai extrair os samples do bloco
std::vector<Sample> SampleBlockParser::parse(const std::vector<uint8_t>& data) {
    std::vector<Sample> samples;

    size_t offset = 0;

    // Primeiro: ler tabela de índices
    std::vector<RawSampleEntry> indexTable;

    while (offset + sizeof(RawSampleEntry) <= data.size()) {
        RawSampleEntry entry;
        std::memcpy(&entry, data.data() + offset, sizeof(RawSampleEntry));
        offset += sizeof(RawSampleEntry);
        indexTable.push_back(entry);
    }

    // Agora: para cada entry, decodificar FLAC
    for (const auto& entry : indexTable) {
        if (entry.offset + entry.size > data.size())
            throw std::runtime_error("SAMPLE_BLOCK corrupted");

        // Extrair bytes do FLAC
        std::vector<uint8_t> flacBytes(entry.size);
        std::memcpy(flacBytes.data(), data.data() + entry.offset, entry.size);

        // Decodificar FLAC (mono)
        Sample sample;
        sample.phonemeId = entry.phonemeId;
        sample.pcm = FlacDecoder::decode(flacBytes);
        sample.sampleRate = FlacDecoder::sampleRate(); // do último decode ou passar parâmetro

        samples.push_back(sample);
    }

    return samples;
}

}
