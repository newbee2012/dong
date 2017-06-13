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
    explicit SoftmaxLayer(){};
    virtual ~SoftmaxLayer() {};
    virtual LayerType getType()
    {
        return SOFTMAX_LAYER;
    }

    virtual void init();
    virtual void forward_cpu();
    virtual void backward();

protected:

    DISABLE_COPY_AND_ASSIGN(SoftmaxLayer);
};

}  // namespace dong

#endif  // DONG_SOFTMAX_LAYER_HPP_
