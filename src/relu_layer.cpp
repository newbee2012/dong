#include <iostream>
#include <common.hpp>
#include <algorithm>
#include "relu_layer.hpp"
using namespace std;

namespace dong
{

ReluLayer::ReluLayer()
{
}

void ReluLayer::forward()
{

    _top_data.reset(new Data(1, 1, _bottom_data->height(), _bottom_data->width(), true));
    const int count = _bottom_data->count();
    for (int i = 0; i < count; ++i)
    {
        _top_data->get(i).value = MAX(_bottom_data->get(i).value, 0.0F);
    }
}

void ReluLayer::backward()
{
}

void ReluLayer::init()
{

}
}
