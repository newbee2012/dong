#ifndef DONG_LAYER_HPP_
#define DONG_LAYER_HPP_
#include "common.hpp"
#include "data.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
enum LayerType_ {INPUT_LAYER, CONVOLUTION_LAYER, POOL_LAYER, FULL_CONNECT_LAYER, RELU_LAYER, SOFTMAX_LAYER};
enum ForwardComputeType_ {INNER_PRODUCT, MAX, RELU};
enum Mode {TRAIN,TEST};

typedef LayerType_ LayerType;
typedef ForwardComputeType_ ForwardComputeType;

class Layer
{
public:
    const char* EnumNames[6]= {"INPUT_LAYER", "CONVOLUTION_LAYER", "POOL_LAYER", "FULL_CONNECT_LAYER", "RELU_LAYER", "SOFTMAX_LAYER"};

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
        /*
        cout<<"--------------------"<< EnumNames[getType()]<<"-----------------------"<<endl;
        cout<<"bottom data forward"<<endl;
        _bottom_data->print();
        cout<<"weight data forward"<<endl;
        if(_weight_data.get()!= NULL)
        {
            _weight_data->print();
        }
        else
        {
            cout<<"---------------"<<endl;
        }
        */

    }

    virtual void backward_cpu() = 0;

    virtual void backward()
    {
        this->backward_cpu();
        /*cout<<"--------------------"<< EnumNames[getType()]<<"-----------------------"<<endl;
        cout<<"bottom diff backward"<<endl;
        _bottom_data->printDiff();
        cout<<"weight diff backward"<<endl;
        if(_weight_data.get()!= NULL)
        {
            _weight_data->printDiff();
        }
        else
        {
            cout<<"---------------"<<endl;
        }
        */
    }

    virtual LayerType getType() = 0;

protected:
    virtual void forwardBase()
    {
        for (int i = 0; i < _bottom_data->count(); ++i)
        {
            const Neuron* b_neuron = _bottom_data->get(i);

            for (int j = 0; j < b_neuron->_forward_neuron.size(); ++j)
            {
                Neuron* t_neuron = b_neuron->_forward_neuron[j];
                Neuron* w_neuron = b_neuron->_weight_neuron[j];
                t_neuron->_value += (b_neuron->_value * w_neuron->_value);
            }
        }
    }

    virtual void backwardBase()
    {
        for (int i = 0; i < _bottom_data->count(); ++i)
        {
            Neuron* b_neuron = _bottom_data->get(i);
            for (int j = 0; j < b_neuron->_forward_neuron.size(); ++j)
            {
                Neuron* t_neuron = b_neuron->_forward_neuron[j];
                Neuron* w_neuron = b_neuron->_weight_neuron[j];
                b_neuron->_diff +=(t_neuron->_diff * w_neuron->_value);
                w_neuron->_diff +=(t_neuron->_diff * b_neuron->_value);
                //w_neuron->_share_count++;
            }
        }

        for (int k = 0; k < _weight_data->count(); ++k)
        {
            Neuron* w_neuron = _weight_data->get(k);
            //w_neuron->_diff = w_neuron->_diff / w_neuron->_share_count;
            switch(getType())
            {
            case CONVOLUTION_LAYER:
            case FULL_CONNECT_LAYER:
                w_neuron->_value -= (BASE_LEARNING_RATE * w_neuron->_diff);
                break;
            default:
                break;
            }
        }
    };

    boost::shared_ptr<Data> _bottom_data;
    boost::shared_ptr<Data> _top_data;
    boost::shared_ptr<Data> _weight_data;
    ForwardComputeType _forwardType;

    DISABLE_COPY_AND_ASSIGN(Layer);
};

}  // namespace dong

#endif  // DONG_LAYER_HPP_
