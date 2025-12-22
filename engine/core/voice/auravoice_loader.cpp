#include "auravoice_loader.h"
#include <stdexcept>

namespace auraloid {

LoadedVoice AuravoiceLoader::loadFromFile(const std::string& path) {
    AuravoiceReader reader(path);

    validateHeader(reader.header());

    LoadedVoice voice;

    for (const auto& block : reader.blocks()) {
        switch (block.type) {
            case BlockType::VOICE_INFO:
                voice.info = reader.readVoiceInfo(block);
                break;

            case BlockType::PHONEME_BLOCK:
                voice.phonemes = reader.readPhonemes(block);
                break;

            case BlockType::SAMPLE_BLOCK:
                voice.samples = reader.readSamples(block);
                break;

            case BlockType::MODEL_BLOCK:
                voice.model = reader.readModel(block);
                break;

            case BlockType::EXPRESSION_BLOCK:
                voice.expressions = reader.readExpressions(block);
                break;

            default:
                // safely ignored
                break;
        }
    }

    return voice;
}

}
