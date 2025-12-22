# Auraloid Sequence Specification

**Format:** `.auraseq`

**Status:** Draft v1.0

This document defines the official project/sequence format used by Auraloid for singing synthesis.

---

## 1. Design Goals

* Human-readable and versionable
* Editor-friendly (piano roll based)
* Independent from voicebanks
* Stable long-term format
* Suitable for GitHub version control

---

## 2. File Format

`.auraseq` files use **UTF-8 encoded JSON**.

The format represents a complete singing project, including tempo, tracks, notes, lyrics, and expression curves.

---

## 3. Root Object

```json
{
  "format": "auraseq",
  "version": "1.0",
  "ppq": 480,
  "tempo": 120,
  "time_signature": "4/4",
  "tracks": []
}
```

### Fields

| Field          | Type    | Description             |
| -------------- | ------- | ----------------------- |
| format         | string  | Always `auraseq`        |
| version        | string  | Format version          |
| ppq            | integer | Pulses per quarter note |
| tempo          | number  | BPM                     |
| time_signature | string  | Musical time signature  |
| tracks         | array   | Track definitions       |

---

## 4. Track Object

Each track represents a single singing voice line.

```json
{
  "id": "track-1",
  "name": "Lead Vocal",
  "voice": "auraloid.metashi",
  "volume": 0.9,
  "pan": 0.0,
  "notes": []
}
```

### Fields

| Field  | Type   | Description             |
| ------ | ------ | ----------------------- |
| id     | string | Unique track identifier |
| name   | string | Display name            |
| voice  | string | Voicebank ID            |
| volume | number | 0.0 – 1.0               |
| pan    | number | -1.0 (L) to 1.0 (R)     |
| notes  | array  | Note events             |

---

## 5. Note Object

Defines a single sung note.

```json
{
  "note": "E4",
  "tick": 1920,
  "length": 480,
  "lyric": "a",
  "phoneme": "a",
  "velocity": 0.8,
  "expression": "soft",
  "pitch_curve": []
}
```

### Fields

| Field       | Type    | Description                  |
| ----------- | ------- | ---------------------------- |
| note        | string  | Musical pitch (e.g. C4, D#5) |
| tick        | integer | Start position (PPQ-based)   |
| length      | integer | Duration in ticks            |
| lyric       | string  | Displayed lyric              |
| phoneme     | string  | Phoneme override (optional)  |
| velocity    | number  | Note strength (0.0 – 1.0)    |
| expression  | string  | Expression preset            |
| pitch_curve | array   | Pitch bend curve             |

---

## 6. Pitch Curve

Pitch curves define fine pitch control within a note.

```json
{
  "t": 0.0,
  "v": 0.0
}
```

### Fields

| Field | Type   | Description                          |
| ----- | ------ | ------------------------------------ |
| t     | number | Normalized time (0.0 – 1.0)          |
| v     | number | Normalized pitch offset (-1.0 – 1.0) |

Curves are evaluated relative to the base note pitch.

---

## 7. Automation (Optional)

Global or track-level automation curves.

```json
"automation": {
  "dynamics": [],
  "breath": []
}
```

Automation curves follow the same structure as pitch curves.

---

## 8. Voice Resolution

Voicebanks are resolved by ID.

* The engine must gracefully handle missing voices
* Editors should display warnings if voices are unavailable

---

## 9. Compatibility Rules

* Unknown fields must be ignored
* Backward compatibility is guaranteed within major versions
* Editors must preserve unknown data

---

## 10. Rendering Behavior

* Notes are rendered sequentially per track
* Expression presets are resolved by the selected voicebank
* Final audio output is engine-dependent

---

## 11. Summary

The `.auraseq` format is:

* Simple
* Explicit
* Extensible
* Editor-driven

It serves as the canonical project format for Auraloid singing synthesis.

