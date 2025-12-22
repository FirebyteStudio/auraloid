# Auraloid Voicebank Specification

**Format:** `.auravoice`

**Status:** Draft v1.0

This document defines the official binary format for Auraloid voicebanks.

---

## 1. Design Goals

* Single-file voicebank distribution
* High performance loading
* Embedded lossless audio (FLAC)
* Support for neural and sample-based voices
* Engine-controlled, user-transparent model storage
* Cross-platform compatibility

---

## 2. File Overview

An `.auravoice` file is a binary container composed of a fixed header followed by structured data blocks.

```
+------------------+
| File Header      |
+------------------+
| VOICE_INFO       |
+------------------+
| PHONEME_BLOCK    |
+------------------+
| TIMBRE_BLOCK     |
+------------------+
| PITCH_BLOCK      |
+------------------+
| SAMPLE_BLOCK*    |
+------------------+
| MODEL_BLOCK*     |
+------------------+
| EXPRESSION_BLOCK |
+------------------+
| LICENSE_BLOCK    |
+------------------+
```

`*` Presence depends on voice type.

---

## 3. File Header

All numeric values use **little-endian** byte order.

| Field       | Type    | Description                  |
| ----------- | ------- | ---------------------------- |
| magic       | char[4] | Always `AURA`                |
| version     | uint16  | Format version               |
| voice_type  | uint8   | 0 = neural, 1 = sample-based |
| flags       | uint8   | Reserved                     |
| header_size | uint32  | Total header size            |
| checksum    | uint32  | CRC32 of file contents       |

---

## 4. VOICE_INFO Block

UTF-8 JSON metadata describing the voice.

```json
{
  "id": "auraloid.metashi",
  "name": "Metashi",
  "language": "ja-JP",
  "voice_type": "neural",
  "gender": "male",
  "range": { "min": "A2", "max": "E6" },
  "author": "Auraloid Team",
  "engine_version": ">=1.0",
  "description": "Soft J-Pop male voice"
}
```

Used by the editor and UI only.

---

## 5. PHONEME_BLOCK

Defines the phoneme inventory supported by the voice.

| Field         | Type    | Description                |
| ------------- | ------- | -------------------------- |
| phoneme_id    | uint16  | Internal identifier        |
| symbol        | string  | UTF-8 phoneme symbol       |
| base_duration | float32 | Default duration (seconds) |

---

## 6. TIMBRE_BLOCK

Stores timbral characteristics of the voice.

* Harmonic color vectors
* Formant tendencies
* Voice identity embeddings

Internal format is engine-defined and opaque.

---

## 7. PITCH_BLOCK

Defines pitch constraints and behavior.

| Field       | Type    |
| ----------- | ------- |
| base_f0     | float32 |
| f0_min      | float32 |
| f0_max      | float32 |
| vibrato_max | float32 |

---

## 8. SAMPLE_BLOCK (Sample-Based Voices Only)

Embedded phoneme samples encoded as FLAC.

| Field        | Type   | Description       |
| ------------ | ------ | ----------------- |
| codec        | uint8  | 1 = FLAC          |
| sample_rate  | uint32 | Sample rate       |
| sample_count | uint32 | Number of samples |

### Sample Index Table

| Field      | Type   |
| ---------- | ------ |
| phoneme_id | uint16 |
| offset     | uint32 |
| size       | uint32 |

FLAC data follows immediately after the index table.

---

## 9. MODEL_BLOCK (Neural Voices Only)

Contains the compiled singing synthesis model.

| Field        | Type   |                      |
| ------------ | ------ | -------------------- |
| model_format | uint8  | 0 = custom, 1 = ONNX |
| model_size   | uint32 |                      |
| model_blob   | bytes  |                      |

The internal structure is opaque to the user.

---

## 10. EXPRESSION_BLOCK

Defines available expressive controls.

| Field         | Type    |
| ------------- | ------- |
| expression_id | uint8   |
| name          | string  |
| min           | float32 |
| max           | float32 |

Examples: `neutral`, `soft`, `power`.

---

## 11. LICENSE_BLOCK

JSON-based license definition.

```json
{
  "commercial_use": true,
  "credit_required": true,
  "political_use": false,
  "ai_training_allowed": false
}
```

The engine must enforce license restrictions when applicable.

---

## 12. Compatibility Notes

* `.auravoice` files are forward-compatible within major versions
* Unknown blocks must be safely skipped
* Editors must not modify binary blocks

---

## 13. Summary

The `.auravoice` format is designed to be:

* Compact
* Secure
* Extensible
* Engine-driven

It represents the canonical voice distribution format for Auraloid.

