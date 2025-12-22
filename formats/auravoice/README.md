# AURASEQ Format Specification

**Format:** `.auraseq`
**Status:** Draft v1.0

This document defines the official **project / sequence format** used by **Auraloid** for singing synthesis.

`.auraseq` represents a complete singing project (similar to VSQX or SVP) and is designed to be editor-friendly, versionable, and independent from voicebanks.

---

## 1. Design Goals

* Human-readable and Git-friendly
* Editor-driven (piano roll based)
* Independent from voicebanks
* Stable long-term compatibility
* Forward-extensible without breaking older versions

---

## 2. File Format

* UTF-8 encoded **JSON**
* One file represents one full singing project
* No embedded audio or voice data

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

| Field  | Type   | Description         |
| ------ | ------ | ------------------- |
| id     | string | Unique track ID     |
| name   | string | Display name        |
| voice  | string | Voicebank ID        |
| volume | number | 0.0 – 1.0           |
| pan    | number | -1.0 (L) to 1.0 (R) |
| notes  | array  | Note events         |

---

## 5. Note Object

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

| Field       | Type    | Description                  |
| ----------- | ------- | ---------------------------- |
| note        | string  | Musical pitch (C4, D#5, etc) |
| tick        | integer | Start position (PPQ-based)   |
| length      | integer | Duration in ticks            |
| lyric       | string  | Displayed lyric              |
| phoneme     | string  | Optional phoneme override    |
| velocity    | number  | 0.0 – 1.0                    |
| expression  | string  | Expression preset            |
| pitch_curve | array   | Pitch bend curve             |

---

## 6. Pitch Curve

```json
{ "t": 0.0, "v": 0.0 }
```

| Field | Type   | Description                 |
| ----- | ------ | --------------------------- |
| t     | number | Normalized time (0.0 – 1.0) |
| v     | number | Pitch offset (-1.0 – 1.0)   |

---

## 7. Automation (Optional)

```json
"automation": {
  "dynamics": [],
  "breath": []
}
```

Automation curves follow the same structure as pitch curves.

---

## 8. Voice Resolution

* Voices are resolved by **ID**
* Missing voices must not break project loading
* Editors should display warnings if voices are unavailable

---

## 9. Compatibility Rules

* Unknown fields must be ignored
* Editors must preserve unknown data
* Backward compatibility guaranteed within major versions

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

It serves as the **canonical project format** for Auraloid singing synthesis.

