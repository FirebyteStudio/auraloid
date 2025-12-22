#include "flac_decoder.h"
#include <dr_flac.h> // https://github.com/mackron/dr_libs
#include <stdexcept>
#include <cstring>

namespace auraloid {

AudioBuffer FlacDecoder::decodeToBuffer(const std::vector<uint8_t>& flacData) {
    drflac* pFlac = drflac_open_memory(flacData.data(), flacData.size(), nullptr);
    if (!pFlac) throw std::runtime_error("Failed to open FLAC memory");

    uint64_t totalSamples = pFlac->totalPCMFrameCount * pFlac->channels;
    std::vector<float> pcm(totalSamples);

    uint64_t framesRead = drflac_read_pcm_frames_f32(pFlac, pFlac->totalPCMFrameCount, pcm.data());
    if (framesRead != pFlac->totalPCMFrameCount) {
        drflac_close(pFlac);
        throw std::runtime_error("Failed to decode all FLAC frames");
    }

    uint32_t sr = pFlac->sampleRate;
    uint8_t channels = static_cast<uint8_t>(pFlac->channels);

    drflac_close(pFlac);

    return AudioBuffer(pcm, sr, channels);
}

} // namespace auraloid
