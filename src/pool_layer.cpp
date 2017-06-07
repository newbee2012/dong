#include <iostream>
#include "pool_layer.hpp"
using namespace std;

namespace dong
{

PoolLayer::PoolLayer()
{
}

void PoolLayer::setUp(const boost::shared_ptr<Data>& data)
{
    _bottom_data = data;
}

void PoolLayer::forward()
{
    int b_n = _bottom_data->num();
    int b_h = _bottom_data->height();
    int b_w = _bottom_data->width();
    int t_n = b_n;
    int t_h = (b_h - _kernel_h) / _stride_h + 1;
    int t_w = (b_w - _kernel_w) / _stride_w + 1;
    _top_data.reset(new Data(t_n, 1, t_h, t_w, true));

    for (int n = 0; n < t_n; n++) {
        for (int h = 0; h < t_h; h++) {
            for (int w = 0; w < t_w; w++) {
                int t_value = 0;

                for (int offset_h = 0; offset_h < _kernel_h; offset_h++) {
                    for (int offset_w = 0; offset_w < _kernel_w; offset_w++) {
                        int b_value = _bottom_data->get(0, 0, h * _stride_h + offset_h, w * _kernel_w + offset_w);
                        t_value = MAX(t_value, b_value);
                    }
                }

                _top_data->set(n, 0, h, w, t_value);
            }
        }
    }
}

void PoolLayer::backward()
{
}

void PoolLayer::init(int kernel_h, int kernel_w, int stride_h, int stride_w)
{
    this->_kernel_h = kernel_h;
    this->_kernel_w = kernel_w;
    this->_stride_h = stride_h;
    this->_stride_w = stride_w;
}

}
