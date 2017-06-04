#ifndef DONG_CONV_LAYER_HPP_
#define DONG_CONV_LAYER_HPP_
#include "common.hpp"
#include "layer.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
class ConvLayer:public Layer
{
public:
    explicit ConvLayer(const boost::shared_ptr<Data>& bottomData);
    virtual LayerType getType(){return CONVOLUTION;}


protected:

    DISABLE_COPY_AND_ASSIGN(ConvLayer);
};

}  // namespace dong

#endif  // DONG_CONV_LAYER_HPP_
