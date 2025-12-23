#include "../neural/neural_onnx.h"

namespace auraloid {

class NeuralVoice : public IVoice {
public:
    NeuralVoice();

    bool loadModel(const std::string& path);

    AudioBuffer<float> render(
        const RenderRequest& request
    ) override;

private:
    NeuralONNX m_onnx;
};

}
