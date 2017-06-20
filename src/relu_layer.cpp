#include <iostream>
#include <common.hpp>
#include <algorithm>
#include "relu_layer.hpp"
using namespace std;

namespace dong
{

void ReluLayer::setUp(const boost::shared_ptr<Data>& data)
{
    Layer::setUp(data);
    _top_data.reset(new Data(1, 1, _bottom_data->height(), _bottom_data->width(), Data::CONSTANT));
    _weight_data.reset(new Data(1, 1, _bottom_data->height(), _bottom_data->width(), Data::CONSTANT));
    for (int i = 0; i < _bottom_data->count(); ++i) {
        Neuron* b_neuron = _bottom_data->get(i);
        Neuron* t_neuron = _top_data->get(i);
        Neuron* w_neuron = _weight_data->get(i);
        b_neuron->_forward_neuron.push_back(t_neuron);
        b_neuron->_weight_neuron.push_back(w_neuron);
        w_neuron->_value = (b_neuron->_value)>0?1.0F:0.0F;
    }
}

void ReluLayer::forward_cpu()
{
    Layer::forwardBase();
}

void ReluLayer::backward_cpu()
{
    Layer::backwardBase();
}

void ReluLayer::init()
{
}
}
