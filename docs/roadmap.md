# Auraloid Roadmap

This document outlines the planned development stages of the Auraloid project.

The roadmap focuses on building a stable core engine first, followed by tooling, usability, and quality improvements.

---

## Phase 0 — Foundation (Current)

**Goal:** Establish a solid technical base.

* Define `.auravoice` specification
* Define `.auraseq` specification
* Repository structure
* Licensing and documentation setup

**Status:** Completed

---

## Phase 1 — Engine MVP (v0.1)

**Goal:** Minimal working singing synthesis pipeline.

### Engine

* `.auravoice` reader (metadata + blocks)
* `.auraseq` parser
* Basic phoneme timing engine
* Simple pitch handling (static pitch)
* Sample-based synthesis (FLAC embedded)
* WAV render output

### Tools

* `voice_packer` (FLAC → `.auravoice`)
* `.auraseq` validator

### Output

* Command-line render tool
* Single-track rendering

**Status:** Completed

---

## Phase 2 — Usability Expansion (v0.2)

**Goal:** Improve musical control and stability.

* Pitch curves support
* Vibrato engine
* Expression presets
* Multi-note smooth transitions
* Multi-track support
* Improved timing accuracy

**Status:** Completed

---

## Phase 3 — Neural Engine Introduction (v0.3)

**Goal:** Introduce neural singing synthesis.

* Neural model runtime integration
* `.auravoice` neural voices
* Model loading and inference pipeline
* Hybrid sample + neural support
* Performance optimizations

**Status:** In progress

---

## Phase 4 — Editor Prototype (v0.4)

**Goal:** Provide a basic desktop editor.

* Piano roll interface
* Note and lyric editing
* Pitch curve editing
* Voice selection
* Real-time preview (non-final quality)

---

## Phase 5 — Quality & Polish (v0.5)

**Goal:** Improve sound quality and workflow.

* Improved expression handling
* Better consonant transitions
* Natural vibrato modeling
* Rendering stability improvements

---

## Phase 6 — Public Release (v1.0)

**Goal:** Stable and usable singing synthesis platform.

* Stable engine API
* Editor usability improvements
* Documentation finalization
* Example voicebank
* Cross-platform builds

---

## Future Ideas (Post v1.0)

* Advanced emotion modeling
* DAW integration
* Plugin formats (VST/AU)
* Community voicebank SDK
* Scriptable automation

---

## Roadmap Principles

* Engine first, UI second
* Stability over features
* Backward compatibility whenever possible
* Clear separation between engine, formats, and editor

---

> Auraloid is built as a long-term platform, not a short-lived experiment.

