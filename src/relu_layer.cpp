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

void ReluLayer::setUp(const boost::shared_ptr<Data>& data)
{
    _bottom_data = data;
}

void ReluLayer::forward()
{

    _top_data.reset(new Data(1, 1, _bottom_data->height(), _bottom_data->width(), true));
    const int count = _bottom_data->count();
    for (int i = 0; i < count; ++i)
    {
        _top_data->set(i,MAX(_bottom_data->get(i), 0.0F));
    }
}

void ReluLayer::backward()
{
}

void ReluLayer::init()
{

}
}
