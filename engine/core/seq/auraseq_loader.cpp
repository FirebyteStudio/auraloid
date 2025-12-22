#include "auraseq_loader.h"
#include <stdexcept>

namespace auraloid {

LoadedSequence AuraseqLoader::load(const std::string& path) {
    AuraseqReader reader(path);
    nlohmann::json j = reader.readJson();

    LoadedSequence seq;
    seq.ppq = j.value("ppq", 480);
    seq.tempo = j.value("tempo", 120.0f);
    seq.timeSignature = j.value("time_signature", "4/4");

    if (!j.contains("tracks") || !j["tracks"].is_array())
        throw std::runtime_error("Invalid .auraseq: missing tracks");

    for (const auto& t : j["tracks"]) {
        SeqTrack track;
        track.id = t.value("id", "");
        track.name = t.value("name", "Track");
        track.voice = t.value("voice", "");
        track.volume = t.value("volume", 1.0f);
        track.pan = t.value("pan", 0.0f);

        if (t.contains("notes") && t["notes"].is_array()) {
            for (const auto& n : t["notes"]) {
                SeqNote note;
                note.note = n.value("note", "C4");
                note.tick = n.value("tick", 0);
                note.length = n.value("length", 480);
                note.lyric = n.value("lyric", "");
                note.phoneme = n.value("phoneme", "");
                note.velocity = n.value("velocity", 1.0f);
                note.expression = n.value("expression", "");
                if (n.contains("pitch_curve") && n["pitch_curve"].is_array()) {
                    for (const auto& p : n["pitch_curve"]) {
                        float t_val = p.value("t", 0.0f);
                        float v_val = p.value("v", 0.0f);
                        note.pitchCurve.emplace_back(t_val, v_val);
                    }
                }
                track.notes.push_back(note);
            }
        }

        seq.tracks.push_back(track);
    }

    return seq;
}

} // namespace auraloid
