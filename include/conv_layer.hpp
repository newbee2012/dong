#ifndef DONG_CONV_LAYER_HPP_
#define DONG_CONV_LAYER_HPP_
#include "common.hpp"
#include "layer.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
class ConvLayer: public Layer
{
public:
    explicit ConvLayer();
    virtual LayerType getType()
    {
        return CONVOLUTION;
    }

    virtual void init(int kernel_num, int kernel_channels, int kernel_h, int kernel_w);
    virtual void forward();
    virtual void backward();

protected:


    DISABLE_COPY_AND_ASSIGN(ConvLayer);
};

}  // namespace dong

#endif  // DONG_CONV_LAYER_HPP_
