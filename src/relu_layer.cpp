#include <iostream>
#include <common.hpp>
#include <algorithm>
#include "relu_layer.hpp"
using namespace std;

namespace dong
{

void ReluLayer::forward_cpu()
{
    _top_data.reset(new Data(1, 1, _bottom_data->height(), _bottom_data->width(), true));
    const int count = _bottom_data->count();

    for (int i = 0; i < count; ++i) {
        _top_data->get(i)._value = MAX(_bottom_data->get(i)._value, 0.0F);
    }
}

void ReluLayer::backward()
{
}

void ReluLayer::init()
{
}
}
