#include "engine/core/voice/auravoice_loader.h"
#include "engine/core/seq/auraseq_loader.h"
#include "engine/core/synth/synth_renderer.h"
#include <iostream>

int main() {
    try {
        // 1️⃣ Carregar voice
        auto voice = auraloid::AuravoiceLoader::load("demo_metashi.auravoice");
        std::cout << "Voice loaded: " << voice.id << " with " 
                  << voice.samples.size() << " samples\n";

        // 2️⃣ Carregar sequence
        auto seq = auraloid::AuraseqLoader::load("hello_world.auraseq");
        std::cout << "Sequence loaded: " << seq.tracks.size() << " tracks\n";

        // 3️⃣ Renderizar track inteira
        auraloid::SynthRenderer synth;
        synth.loadVoice(voice);
        synth.loadSequence(seq);

        auraloid::AudioBuffer finalBuffer = synth.render();
        std::cout << "Rendered audio buffer: " << finalBuffer.getPCM().size()
                  << " samples at " << finalBuffer.getSampleRate() << " Hz\n";

        // 4️⃣ Playback placeholder
        std::cout << "Demo V1 rendering complete! (playback not implemented yet)\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
