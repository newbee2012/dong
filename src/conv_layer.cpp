#include <iostream>
#include "conv_layer.hpp"
using namespace std;

namespace dong
{

ConvLayer::ConvLayer()
{
}

void ConvLayer::forward()
{

    int b_n = _bottom_data->num();
    int b_h = _bottom_data->height();
    int b_w = _bottom_data->width();
    int k_n = _weight_data->num();
    int k_h = _weight_data->height();
    int k_w = _weight_data->width();
    int t_n = k_n;
    int t_h = b_h - k_h + 1;
    int t_w = b_w - k_w + 1;
    _top_data.reset(new Data(t_n, 1, t_h, t_w, true));

    for (int n = 0; n < t_n; n++) {
        for (int h = 0; h < t_h; h++) {
            for (int w = 0; w < t_w; w++) {
                float t_value = 0;

                for (int offset_h = 0; offset_h < k_h; offset_h++) {
                    for (int offset_w = 0; offset_w < k_w; offset_w++) {
                        float b_value = _bottom_data->get(0, 0, h + offset_h, w + offset_w).value;
                        float k_value = _weight_data->get(n, 0, offset_h, offset_w).value;
                        t_value += (b_value * k_value);
                    }
                }

                _top_data->get(n, 0, h, w).value = t_value;
            }
        }
    }

}

void ConvLayer::backward()
{
}

void ConvLayer::init(int kernel_num, int kernel_channels, int kernel_h, int kernel_w)
{
    _weight_data.reset(new Data(kernel_num, kernel_channels, kernel_h, kernel_w, true));
}

}
