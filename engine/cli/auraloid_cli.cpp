#include <iostream>
#include <string>

#include "engine/voice/auravoice_reader.h"
#include "engine/seq/auraseq_reader.h"
#include "engine/synth/synth_renderer.h"
#include "engine/io/audio/wav_writer.h"

using namespace auraloid;

static void printUsage() {
    std::cout << "Auraloid CLI v1.0\n";
    std::cout << "Usage:\n";
    std::cout << "  auraloid render <voice.auravoice> <song.auraseq> <output.wav>\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];

    if (command != "render") {
        printUsage();
        return 1;
    }

    if (argc != 5) {
        printUsage();
        return 1;
    }

    std::string voicePath = argv[2];
    std::string seqPath   = argv[3];
    std::string outPath   = argv[4];

    std::cout << "[Auraloid] Loading voice...\n";
    AuraVoiceReader voiceReader;
    if (!voiceReader.load(voicePath)) {
        std::cerr << "[Error] Failed to load auravoice\n";
        return 1;
    }

    std::cout << "[Auraloid] Loading sequence...\n";
    AuraSeqReader seqReader;
    if (!seqReader.load(seqPath)) {
        std::cerr << "[Error] Failed to load auraseq\n";
        return 1;
    }

    std::cout << "[Auraloid] Rendering...\n";
    SynthRenderer renderer;
    renderer.setVoice(voiceReader.getVoice());
    renderer.setSequence(seqReader.getSequence());

    auto buffer = renderer.render();

    if (buffer.empty()) {
        std::cerr << "[Error] Render failed\n";
        return 1;
    }

    std::cout << "[Auraloid] Writing WAV...\n";
    if (!WavWriter::write(outPath, buffer, 44100)) {
        std::cerr << "[Error] Failed to write WAV\n";
        return 1;
    }

    std::cout << "[Auraloid] Done 🎉\n";
    std::cout << "Output: " << outPath << "\n";

    return 0;
}
