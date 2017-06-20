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

    for (int i = 0; i < count; ++i) {
        maxValue = MAX(maxValue, _bottom_data->get(i)->_value);
    }

    double sumExp = 0.0F;

    for (int i = 0; i < count; ++i) {
        float expValue = exp(_bottom_data->get(i)->_value / (maxValue / 10)) ;
        _top_data->get(i)->_value = expValue;
        sumExp += expValue;
    }

    for (int i = 0; i < count; ++i) {
        _top_data->get(i)->_value = (float)_top_data->get(i)->_value / sumExp;
    }
}

void SoftmaxLayer::backward_cpu()
{
}

void SoftmaxLayer::init()
{
}
}
