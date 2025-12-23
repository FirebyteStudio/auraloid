#pragma once
#include <string>
#include <vector>

namespace auraloid {

class WavWriter {
public:
    static bool write(
        const std::string& path,
        const std::vector<float>& samples,
        int sampleRate = 44100
    );
};

} // namespace auraloid
