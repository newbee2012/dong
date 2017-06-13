#ifndef DONG_LAYER_HPP_
#define DONG_LAYER_HPP_
#include "common.hpp"
#include "data.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

enum LayerType_ {INPUT, DATA, CONVOLUTION, POOL, FULL_CONNECT, RELU, SOFTMAX};
enum ForwardComputeType_ {INNER_PRODUCT, MAX};
typedef LayerType_ LayerType;
typedef ForwardComputeType_ ForwardComputeType;

class Layer
{
public:
    Layer() {};
    virtual ~Layer() {};
    virtual void setUp(const boost::shared_ptr<Data>& data)
    {
        this->_bottom_data = data;
    }

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

    virtual void forward_cpu() = 0;

    virtual void forward()
    {
        this->forward_cpu();
    }

    virtual LayerType getType() = 0;

protected:
    virtual void forwardBase(ForwardComputeType type)
    {
        int count = _bottom_data->count();
        for (int i = 0; i < count; ++i)
        {
            Neuron& b_neuron = _bottom_data->get(i);
            for(int j=0; j<b_neuron._forward_neuron.size(); ++j)
            {
                Neuron* t_neuron = b_neuron._forward_neuron[j];
                Neuron* w_neuron = b_neuron._weight_neuron[j];
                if(type == INNER_PRODUCT)
                {
                    t_neuron->_value += (b_neuron._value * w_neuron->_value);
                }
                else if(type == MAX)
                {
                    {
                        t_neuron->_value = MAX(t_neuron->_value, b_neuron._value);
                    }

                }
            }
        }
    }

    virtual void backward() {};

    boost::shared_ptr<Data> _bottom_data;
    boost::shared_ptr<Data> _top_data;
    boost::shared_ptr<Data> _weight_data;
    ForwardComputeType _forwardType;
    DISABLE_COPY_AND_ASSIGN(Layer);
};

}  // namespace dong

#endif  // DONG_LAYER_HPP_
