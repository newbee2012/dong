#include <iostream>
#include <common.hpp>
#include <algorithm>
#include "softmax_layer.hpp"

using namespace std;

namespace dong
{

void SoftmaxLayer::forward_cpu()
{
    _top_data.reset(new Data(1, 1, _bottom_data->height(), _bottom_data->width(), Data::CONSTANT));
    const int count = _bottom_data->count();
    float maxValue = 0.0F;

    for (int i = 0; i < count; ++i)
    {
        maxValue = MAX(maxValue, _bottom_data->get(i)->_value);
    }

    double sumExp = 0.0F;

    for (int i = 0; i < count; ++i)
    {
        float expValue = exp(_bottom_data->get(i)->_value-maxValue) ;
        _top_data->get(i)->_value = expValue;
        sumExp += expValue;
    }

    for (int i = 0; i < count; ++i)
    {
        _top_data->get(i)->_value = (float)_top_data->get(i)->_value / sumExp;
    }

    if(this->mode == TRAIN)
    {
        loss = -log(std::max(_top_data->get(label)->_value, FLT_MIN));
    }
}

void SoftmaxLayer::backward_cpu()
{
    for (int i = 0; i < _bottom_data->count(); ++i)
    {
        Neuron* b_neuron = _bottom_data->get(i);
        Neuron* t_neuron = _top_data->get(i);
        b_neuron->_diff = t_neuron->_value;
    }

    _bottom_data->get(label)->_diff -= 1;
}

void SoftmaxLayer::setLabel(int label)
{
    this->label = label;
}

void SoftmaxLayer::init()
{
}

}
