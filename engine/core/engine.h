#pragma once

#include <string>
#include <memory>

namespace auraloid {

// Forward declarations
class Voice;
class Sequence;

// Engine version info
struct EngineVersion {
    int major;
    int minor;
    int patch;
};

class Engine {
public:
    Engine();
    ~Engine();

    // Non-copyable
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    // Version
    static EngineVersion version();

    // Core lifecycle
    bool initialize();
    void shutdown();

    // Loading
    std::shared_ptr<Voice> loadVoice(const std::string& auravoicePath);
    std::shared_ptr<Sequence> loadSequence(const std::string& auraseqPath);

    // Rendering (MVP)
    bool renderToWav(const Sequence& sequence,
                     const Voice& voice,
                     const std::string& outputPath);

private:
    bool initialized_ = false;
};

} // namespace auraloid

