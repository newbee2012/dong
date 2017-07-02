#include <iostream>
#include "neuron.hpp"
using namespace std;

namespace dong
{


void Neuron::forward()
{
    for (int i = 0; i < _forward_neuron.size(); ++i)
    {
        Neuron* t_neuron = _forward_neuron[i];
        Neuron* w_neuron = _weight_neuron[i];
        Neuron* b_neuron = _bias_data[i];
        t_neuron->_value += (_value * w_neuron->_value + b_neuron->_value);
    }
}

void Neuron::backward()
{
    for (int i = 0; i < _forward_neuron.size(); ++i)
    {
        Neuron* t_neuron = _forward_neuron[i];
        Neuron* w_neuron = _weight_neuron[i];
        _diff += (t_neuron->_diff * w_neuron->_value);
        w_neuron->_diff += (t_neuron->_diff * _value);
    }
}



}
