#include "auraseq_loader.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace auraloid {

LoadedSequence AuraseqLoader::load(const std::string& path) {
    LoadedSequence seq;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[AuraseqLoader] Failed to open " << path << "\n";
        return seq;
    }

    json j;
    file >> j;

    seq.ppq = j.value("ppq", 480);
    seq.tempo = j.value("tempo", 120.0f);
    seq.timeSignature = j.value("timeSignature", "4/4");

    for (const auto& jt : j["tracks"]) {
        SeqTrack track;
        track.id     = jt.value("id", "");
        track.name   = jt.value("name", "track");
        track.voice  = jt.value("voice", "");
        track.volume = jt.value("volume", 1.0f);
        track.pan    = jt.value("pan", 0.0f);

        for (const auto& jn : jt["notes"]) {
            SeqNote note;
            note.note     = jn.value("note", "A4");
            note.tick     = jn.value("tick", 0);
            note.length  = jn.value("length", seq.ppq / 2);
            note.lyric   = jn.value("lyric", "");
            note.phoneme = jn.value("phoneme", "");
            note.velocity = jn.value("velocity", 1.0f);
            note.expression = jn.value("expression", "neutral");

            if (jn.contains("pitchCurve")) {
                for (const auto& p : jn["pitchCurve"]) {
                    float t = p[0];
                    float v = p[1];
                    note.pitchCurve.emplace_back(t, v);
                }
            }

            track.notes.push_back(note);
        }

        seq.tracks.push_back(track);
    }

    return seq;
}

} // namespace auraloid
