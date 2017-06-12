#include <iostream>
#include "conv_layer.hpp"
#include "neuron.hpp"
using namespace std;

namespace dong
{

void ConvLayer::init(int kernel_num, int kernel_channels, int kernel_h, int kernel_w)
{
    _weight_data.reset(new Data(kernel_num, kernel_channels, kernel_h, kernel_w, true));
}

void ConvLayer::setUp(const boost::shared_ptr<Data>& data)
{
    Layer::setUp(data);
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

    for (int n = 0; n < t_n; n++)
    {
        for (int h = 0; h < t_h; h++)
        {
            for (int w = 0; w < t_w; w++)
            {
                float t_value = 0;

                for (int offset_h = 0; offset_h < k_h; offset_h++)
                {
                    for (int offset_w = 0; offset_w < k_w; offset_w++)
                    {
                        Neuron& b_neuron = _bottom_data->get(0, 0, h + offset_h, w + offset_w);
                        Neuron& t_neuron = _top_data->get(n, 0, h, w);
                        Neuron& w_neuron = _weight_data->get(n, 0, offset_h, offset_w);

                        b_neuron._forward_neuron.push_back(&t_neuron);
                        b_neuron._weight_neuron.push_back(&w_neuron);
                    }
                }
            }
        }
    }
}

void ConvLayer::forward()
{
    int b_n = _bottom_data->num();
    int b_h = _bottom_data->height();
    int b_w = _bottom_data->width();

    for (int n = 0; n < b_n; n++)
    {
        for (int h = 0; h < b_h; h++)
        {
            for (int w = 0; w < b_w; w++)
            {
                Neuron& b_neuron = _bottom_data->get(n, 0, h, w);
                for(int i=0;i<b_neuron._forward_neuron.size();++i)
                {
                    Neuron* t_neuron = b_neuron._forward_neuron[i];
                    Neuron* w_neuron = b_neuron._weight_neuron[i];
                    t_neuron->_value += (b_neuron._value * w_neuron->_value);
                }
            }
        }
    }
}

void ConvLayer::backward()
{
}



}
