#pragma once
#include <string>
#include "../loaded_voice.h"
#include "../auravoice_reader.h"
#include "blocks/voice_info.h"
#include "blocks/phoneme_block.h"
#include "blocks/sample_block.h"
#include "blocks/model_block.h"

namespace auraloid {

class AuravoiceLoader {
public:
    // Carrega um arquivo .auravoice e retorna um LoadedVoice
    static LoadedVoice load(const std::string& path);
};

}
