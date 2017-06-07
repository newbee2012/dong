#include <iostream>
#include "inner_product_layer.hpp"
using namespace std;

namespace dong
{

InnerProductLayer::InnerProductLayer()
{
}

void InnerProductLayer::setUp(const boost::shared_ptr<Data>& data)
{
    _bottom_data = data;
}

void InnerProductLayer::forward()
{
    int b_n = _bottom_data->num();
    int b_h = _bottom_data->height();
    int b_w = _bottom_data->width();
    int t_n = 1;
    int t_h = 1;
    int t_w = _num;
    _top_data.reset(new Data(t_n, 1, t_h, t_w, true));

    for (int n = 0; n < t_n; n++) {
        for (int h = 0; h < t_h; h++) {
            for (int w = 0; w < t_w; w++) {
                int t_value = 0;

                for (int bh = 0; bh < b_h; bh++) {
                    for (int bw = 0; bw < b_w; bw++) {
                        int b_value = _bottom_data->get(0, 0, bh, bw);
                        t_value = MAX(t_value, b_value);
                        _top_data->set(n, 0, h, w, t_value);
                    }
                }


            }
        }
    }
}

void InnerProductLayer::backward()
{
}

void InnerProductLayer::init(int num)
{
    this->_num = num;
    this->_weight.reset(new Data(1,1, _bottom_data->count(), num, true));
}

}