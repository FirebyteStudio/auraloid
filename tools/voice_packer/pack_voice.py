#!/usr/bin/env python3
"""
Auraloid Voice Packer
Packs a voice directory into a single .auravoice binary file.
"""

import json
import struct
import sys
import zlib
from pathlib import Path

MAGIC = b"AURA"
VERSION = 0x0100  # v1.0

# -----------------------------
# Utils
# -----------------------------

def die(msg):
    print(f"[ERROR] {msg}")
    sys.exit(1)

def read_json(path: Path):
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except Exception as e:
        die(f"Invalid JSON {path.name}: {e}")

def write_block(out, block_id: bytes, payload: bytes):
    out.write(block_id)
    out.write(struct.pack("<I", len(payload)))
    out.write(payload)

# -----------------------------
# Block builders
# -----------------------------

def build_voice_info(path: Path) -> bytes:
    data = read_json(path)
    raw = json.dumps(data, ensure_ascii=False).encode("utf-8")
    return raw

def build_phoneme_block(path: Path) -> bytes:
    data = read_json(path)
    buf = bytearray()
    for p in data:
        buf += struct.pack("<H", p["id"])
        symbol = p["symbol"].encode("utf-8")
        buf += struct.pack("<H", len(symbol))
        buf += symbol
        buf += struct.pack("<f", float(p["base_duration"]))
    return bytes(buf)

def build_pitch_block(path: Path) -> bytes:
    data = read_json(path)
    return struct.pack(
        "<ffff",
        float(data["base_f0"]),
        float(data["f0_min"]),
        float(data["f0_max"]),
        float(data["vibrato_max"])
    )

def build_expression_block(path: Path) -> bytes:
    data = read_json(path)
    buf = bytearray()
    for e in data:
        name = e["name"].encode("utf-8")
        buf += struct.pack("<B", e["id"])
        buf += struct.pack("<H", len(name))
        buf += name
        buf += struct.pack("<ff", e["min"], e["max"])
    return bytes(buf)

def build_license_block(path: Path) -> bytes:
    raw = json.dumps(read_json(path), ensure_ascii=False).encode("utf-8")
    return raw

def build_model_block(path: Path) -> bytes:
    blob = path.read_bytes()
    return struct.pack("<BI", 1, len(blob)) + blob  # 1 = ONNX

# -----------------------------
# Main packer
# -----------------------------

def pack_voice(input_dir: Path, output_file: Path):
    if not input_dir.exists():
        die("Voice directory not found")

    buffer = bytearray()

    # Header placeholder
    buffer += MAGIC
    buffer += struct.pack("<HBBII", VERSION, 0, 0, 0, 0)

    # Blocks
    write_block(buffer, b"VINF", build_voice_info(input_dir / "voice_info.json"))
    write_block(buffer, b"PHON", build_phoneme_block(input_dir / "phonemes.json"))
    write_block(buffer, b"PITC", build_pitch_block(input_dir / "pitch.json"))

    expr = input_dir / "expressions.json"
    if expr.exists():
        write_block(buffer, b"EXPR", build_expression_block(expr))

    model = input_dir / "model.onnx"
    if model.exists():
        write_block(buffer, b"MODL", build_model_block(model))

    lic = input_dir / "license.json"
    if lic.exists():
        write_block(buffer, b"LICN", build_license_block(lic))

    # Finalize header
    checksum = zlib.crc32(buffer[16:])
    header_size = 16

    struct.pack_into("<I", buffer, 8, header_size)
    struct.pack_into("<I", buffer, 12, checksum)

    output_file.write_bytes(buffer)
    print(f"[OK] Voice packed → {output_file.name}")

# -----------------------------
# CLI
# -----------------------------

def main():
    if len(sys.argv) != 3:
        print("Usage: pack_voice.py <voice_dir> <output.auravoice>")
        sys.exit(1)

    pack_voice(Path(sys.argv[1]), Path(sys.argv[2]))

if __name__ == "__main__":
    main()

