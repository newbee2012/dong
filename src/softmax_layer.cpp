#include <iostream>
#include <common.hpp>
#include <algorithm>
#include "softmax_layer.hpp"

using namespace std;

namespace dong
{

SoftmaxLayer::SoftmaxLayer()
{
}

void SoftmaxLayer::setUp(const boost::shared_ptr<Data>& data)
{
    _bottom_data = data;
}

void SoftmaxLayer::forward()
{

    _top_data.reset(new Data(1, 1, _bottom_data->height(), _bottom_data->width(), true));
    const int count = _bottom_data->count();

    float maxValue = 0.0F;
    for (int i = 0; i < count; ++i)
    {
        maxValue = MAX(maxValue, _bottom_data->get(i));
    }


    double sumExp = 0.0F;
    for (int i = 0; i < count; ++i)
    {
        float expValue = exp(_bottom_data->get(i)/ (maxValue/10)) ;
        _top_data->set(i,expValue);
        sumExp += expValue;
    }

    for (int i = 0; i < count; ++i)
    {
        _top_data->set(i,(float)_top_data->get(i)/sumExp);
    }
}

void SoftmaxLayer::backward()
{
}

void SoftmaxLayer::init()
{

}
}
