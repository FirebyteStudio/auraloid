#!/usr/bin/env python3
"""
Auraloid Sequence Validator
Validates .auraseq files against the AURASEQ v1.0 specification.
"""

import json
import sys
from pathlib import Path

# -----------------------------
# Utils
# -----------------------------

def error(msg: str):
    print(f"[ERROR] {msg}")
    sys.exit(1)

def load_json(path: Path):
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception as e:
        error(f"Invalid JSON: {e}")

# -----------------------------
# Validation helpers
# -----------------------------

def require(obj, key, expected_type, ctx):
    if key not in obj:
        error(f"Missing '{key}' in {ctx}")
    if not isinstance(obj[key], expected_type):
        error(f"Invalid type for '{key}' in {ctx}")

def is_valid_pitch(note: str) -> bool:
    import re
    return bool(re.match(r"^[A-G](#|b)?[0-8]$", note))

# -----------------------------
# Validators
# -----------------------------

def validate_pitch_curve(curve, ctx):
    if not isinstance(curve, list):
        error(f"pitch_curve must be an array in {ctx}")

    for p in curve:
        require(p, "t", (int, float), "pitch_curve point")
        require(p, "v", (int, float), "pitch_curve point")

        if not 0.0 <= p["t"] <= 1.0:
            error("pitch_curve.t must be between 0.0 and 1.0")
        if not -1.0 <= p["v"] <= 1.0:
            error("pitch_curve.v must be between -1.0 and 1.0")

def validate_note(note, track_id):
    ctx = f"note in track '{track_id}'"

    require(note, "note", str, ctx)
    require(note, "tick", int, ctx)
    require(note, "length", int, ctx)
    require(note, "lyric", str, ctx)

    if not is_valid_pitch(note["note"]):
        error(f"Invalid pitch '{note['note']}' in {ctx}")

    if note["tick"] < 0:
        error(f"tick must be >= 0 in {ctx}")

    if note["length"] <= 0:
        error(f"length must be > 0 in {ctx}")

    if "velocity" in note and not 0.0 <= note["velocity"] <= 1.0:
        error(f"velocity must be 0.0–1.0 in {ctx}")

    if "pitch_curve" in note:
        validate_pitch_curve(note["pitch_curve"], ctx)

def validate_track(track):
    ctx = f"track '{track.get('id', '?')}'"

    require(track, "id", str, ctx)
    require(track, "name", str, ctx)
    require(track, "voice", str, ctx)
    require(track, "volume", (int, float), ctx)
    require(track, "pan", (int, float), ctx)
    require(track, "notes", list, ctx)

    if not 0.0 <= track["volume"] <= 1.0:
        error(f"volume must be 0.0–1.0 in {ctx}")

    if not -1.0 <= track["pan"] <= 1.0:
        error(f"pan must be -1.0–1.0 in {ctx}")

    for note in track["notes"]:
        validate_note(note, track["id"])

def validate_root(data):
    require(data, "format", str, "root")
    require(data, "version", str, "root")
    require(data, "ppq", int, "root")
    require(data, "tempo", (int, float), "root")
    require(data, "time_signature", str, "root")
    require(data, "tracks", list, "root")

    if data["format"] != "auraseq":
        error("format must be 'auraseq'")

    if data["ppq"] <= 0:
        error("ppq must be > 0")

    if data["tempo"] <= 0:
        error("tempo must be > 0")

    for track in data["tracks"]:
        validate_track(track)

# -----------------------------
# Main
# -----------------------------

def main():
    if len(sys.argv) != 2:
        print("Usage: validate_seq.py <file.auraseq>")
        sys.exit(1)

    path = Path(sys.argv[1])
    if not path.exists():
        error("File not found")

    data = load_json(path)
    validate_root(data)

    print("[OK] auraseq file is valid")

if __name__ == "__main__":
    main()

