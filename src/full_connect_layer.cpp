#include <iostream>
#include "full_connect_layer.hpp"
using namespace std;

namespace dong
{

void FullConnectLayer::setUp(const boost::shared_ptr<Data>& data)
{
    Layer::setUp(data);
    this->_weight_data.reset(new Data(1, 1, _bottom_data->count(), _num, Data::RANDOM));
    int b_n = _bottom_data->num();
    int b_h = _bottom_data->height();
    int b_w = _bottom_data->width();
    int t_n = 1;
    int t_h = 1;
    int t_w = _num;
    _top_data.reset(new Data(t_n, 1, t_h, t_w, Data::CONSTANT));

    for (int n = 0; n < t_n; n++) {
        for (int h = 0; h < t_h; h++) {
            for (int w = 0; w < t_w; w++) {
                Neuron* t_neuron = _top_data->get(n, 0, h, w);

                for (int i = 0; i < _bottom_data->count(); i++) {
                    Neuron* b_neuron = _bottom_data->get(i);
                    Neuron* w_neuron = _weight_data->get(0, 0, i, w);
                    b_neuron->_forward_neuron.push_back(t_neuron);
                    b_neuron->_weight_neuron.push_back(w_neuron);
                }
            }
        }
    }
}

void FullConnectLayer::forward_cpu()
{
    Layer::forwardBase();
}

void FullConnectLayer::backward_cpu()
{
    Layer::backwardBase();
}

void FullConnectLayer::init(int num)
{
    this->_num = num;
}

}
