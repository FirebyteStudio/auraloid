#include "wav_writer.h"
#include <fstream>
#include <cstdint>
#include <algorithm>

namespace auraloid {

static void writeInt(std::ofstream& out, uint32_t value) {
    out.write(reinterpret_cast<const char*>(&value), 4);
}

static void writeShort(std::ofstream& out, uint16_t value) {
    out.write(reinterpret_cast<const char*>(&value), 2);
}

bool WavWriter::write(
    const std::string& path,
    const std::vector<float>& samples,
    int sampleRate
) {
    std::ofstream out(path, std::ios::binary);
    if (!out) return false;

    const int numChannels = 1;
    const int bitsPerSample = 16;
    const int byteRate = sampleRate * numChannels * bitsPerSample / 8;
    const int blockAlign = numChannels * bitsPerSample / 8;
    const uint32_t dataSize = samples.size() * blockAlign;

    // RIFF header
    out.write("RIFF", 4);
    writeInt(out, 36 + dataSize);
    out.write("WAVE", 4);

    // fmt chunk
    out.write("fmt ", 4);
    writeInt(out, 16);
    writeShort(out, 1); // PCM
    writeShort(out, numChannels);
    writeInt(out, sampleRate);
    writeInt(out, byteRate);
    writeShort(out, blockAlign);
    writeShort(out, bitsPerSample);

    // data chunk
    out.write("data", 4);
    writeInt(out, dataSize);

    // PCM data
    for (float s : samples) {
        s = std::clamp(s, -1.0f, 1.0f);
        int16_t pcm = static_cast<int16_t>(s * 32767);
        out.write(reinterpret_cast<const char*>(&pcm), sizeof(int16_t));
    }

    out.close();
    return true;
}

} // namespace auraloid
