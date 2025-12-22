#include "audio_buffer.h"

#include <string>
#include <stdexcept>

namespace auraloid::audio {

// NOTE:
// This is a placeholder FLAC decoder implementation.
// The actual decoding logic will be implemented using
// an external FLAC library or a custom decoder.

AudioBuffer decodeFlac(const std::string& path) {
    // For now, we only validate the file path and return
    // an empty AudioBuffer as a stub.

    if (path.empty()) {
        throw std::runtime_error("FLAC path is empty");
    }

    // Default dummy buffer (mono, 44.1kHz, 0 frames)
    AudioBuffer buffer(1, 44100);
    buffer.resize(0);

    return buffer;
}

} // namespace auraloid::audio

