#ifndef DONG_SOFTMAX_LAYER_HPP_
#define DONG_SOFTMAX_LAYER_HPP_
#include "common.hpp"
#include "layer.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
class SoftmaxLayer: public Layer
{
public:

    explicit SoftmaxLayer(Mode mode) {this->mode = mode;};
    virtual ~SoftmaxLayer() {};
    virtual LayerType getType()
    {
        return SOFTMAX_LAYER;
    }

    virtual void init();
    virtual void setLabel(int label);
    virtual void forward_cpu();
    virtual void backward_cpu();
    float getLoss(){return loss;};
private:
    Mode mode = TRAIN;
    float loss = 0.0F;
    int label = 0;
protected:

    DISABLE_COPY_AND_ASSIGN(SoftmaxLayer);
};

}  // namespace dong

#endif  // DONG_SOFTMAX_LAYER_HPP_
