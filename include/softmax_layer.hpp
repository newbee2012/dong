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
    explicit SoftmaxLayer();
    virtual LayerType getType()
    {
        return SOFTMAX;
    }
    virtual void setUp(const boost::shared_ptr<Data>& bottomData);
    virtual void init();
    virtual void forward();
    virtual void backward();

protected:

    DISABLE_COPY_AND_ASSIGN(SoftmaxLayer);
};

}  // namespace dong

#endif  // DONG_SOFTMAX_LAYER_HPP_
