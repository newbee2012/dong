#ifndef DONG_RELU_LAYER_HPP_
#define DONG_RELU_LAYER_HPP_
#include "common.hpp"
#include "layer.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
class ReluLayer: public Layer
{
public:
    explicit ReluLayer();
    virtual LayerType getType()
    {
        return RELU;
    }

    virtual void init();
    virtual void forward();
    virtual void backward();

protected:

    DISABLE_COPY_AND_ASSIGN(ReluLayer);
};

}  // namespace dong

#endif  // DONG_RELU_LAYER_HPP_
