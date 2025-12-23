#include <iostream>
#include <string>

#include "engine/core/synth/synth_renderer.h"
#include "engine/core/synth/mixer.h"
#include "engine/io/auravoice_loader.h"
#include "engine/io/auraseq_parser.h"
#include "engine/io/wav_writer.h"

using namespace auraloid;

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cout <<
            "Auraloid Render v0.2\n"
            "Usage:\n"
            "  auraloid_render "
            "--voice voice.auravoice "
            "--seq song.auraseq "
            "--out output.wav\n";
        return 0;
    }

    std::string voicePath;
    std::string seqPath;
    std::string outPath = "output.wav";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--voice" && i + 1 < argc)
            voicePath = argv[++i];
        else if (arg == "--seq" && i + 1 < argc)
            seqPath = argv[++i];
        else if (arg == "--out" && i + 1 < argc)
            outPath = argv[++i];
    }

    if (voicePath.empty() || seqPath.empty()) {
        std::cerr << "[CLI] Missing input files\n";
        return 1;
    }

    // Load voice
    AuraVoiceLoader voiceLoader;
    auto voice = voiceLoader.load(voicePath);
    if (!voice) {
        std::cerr << "[CLI] Failed to load voice\n";
        return 1;
    }

    // Load sequence
    AuraSeqParser seqParser;
    AuraSeq sequence;
    if (!seqParser.parse(seqPath, sequence)) {
        std::cerr << "[CLI] Failed to load sequence\n";
        return 1;
    }

    // Render tracks
    SynthRenderer renderer;
    renderer.setVoice(voice);

    std::vector<AudioBuffer<float>> tracks;
    std::vector<float> volumes;
    std::vector<float> pans;

    for (const auto& track : sequence.tracks) {
        renderer.setSequence({ { track } });
        tracks.push_back(renderer.render());

        volumes.push_back(track.volume);
        pans.push_back(track.pan);
    }

    // Mix stereo
    Mixer mixer;
    AudioBuffer<float> stereo =
        mixer.mixStereo(tracks, volumes, pans);

    // Write WAV
    if (!WavWriter::write(outPath, stereo, 44100)) {
        std::cerr << "[CLI] Failed to write WAV\n";
        return 1;
    }

    std::cout << "[CLI] Render complete: " << outPath << "\n";
    return 0;
}
