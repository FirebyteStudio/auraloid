#include "auravoice_loader.h"
#include <stdexcept>
#include <iostream>

namespace auraloid {

LoadedVoice AuravoiceLoader::load(const std::string& path) {
    AuravoiceReader reader(path);

    LoadedVoice voice;

    for (const auto& block : reader.blocks()) {
        std::vector<uint8_t> raw;
        reader.readBlockData(block, raw);

        switch (block.type) {
            case BlockType::VOICE_INFO: {
                std::string jsonStr(raw.begin(), raw.end());
                voice.info = VoiceInfoParser::parse(jsonStr);
                voice.isNeural = (voice.info.voiceType == "neural");
                break;
            }

            case BlockType::PHONEME_BLOCK:
                voice.phonemes = PhonemeBlockParser::parse(raw);
                break;

            case BlockType::SAMPLE_BLOCK:
                voice.samples = SampleBlockParser::parse(raw);
                break;

            case BlockType::MODEL_BLOCK:
                voice.model = ModelBlockParser::parse(raw);
                voice.isNeural = true;
                break;

            case BlockType::EXPRESSION_BLOCK:
                // Implementar depois
                break;

            default:
                std::cerr << "Unknown block type: " << static_cast<int>(block.type) << " skipped.\n";
                break;
        }
    }

    // Valida blocos obrigatórios
    if (voice.info.id.empty())
        throw std::runtime_error("VOICE_INFO missing or invalid");

    if (voice.isNeural && voice.model.blob.empty())
        throw std::runtime_error("MODEL_BLOCK missing for neural voice");

    if (!voice.isNeural && voice.samples.empty())
        throw std::runtime_error("SAMPLE_BLOCK missing for sample-based voice");

    return voice;
}

}
