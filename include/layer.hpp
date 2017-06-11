#ifndef DONG_LAYER_HPP_
#define DONG_LAYER_HPP_
#include "common.hpp"
#include "data.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

enum LayerType {INPUT, DATA, CONVOLUTION, POOL, INNER_PRODUCT, RELU, SOFTMAX};

class Layer
{
public:
    Layer() {};
    virtual ~Layer() {};
    virtual boost::shared_ptr<Data> getBottomData()
    {
        return _bottom_data;
    }
    virtual boost::shared_ptr<Data> getTopData()
    {
        return _top_data;
    }
    virtual boost::shared_ptr<Data> getWeightData()
    {
        return _weight_data;
    }
    virtual void forward() {};
    virtual void backward() {};
protected:
    boost::shared_ptr<Data> _bottom_data;
    boost::shared_ptr<Data> _top_data;
    boost::shared_ptr<Data> _weight_data;
    virtual LayerType getType() = 0;
    //DISABLE_COPY_AND_ASSIGN(Layer);
};

}  // namespace dong

#endif  // DONG_LAYER_HPP_
