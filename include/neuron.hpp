#ifndef DONG_NEURON_LAYER_HPP_
#define DONG_NEURON_LAYER_HPP_
#include "common.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

class Neuron
{
public:
    Neuron()
    {
        this->_value = 0;
    }

    Neuron(float value)
    {
        this->_value = value;
    }

    void forward();
    float _value;
    float _diff;

    vector< Neuron* > _forward_neuron;
    vector< Neuron* > _weight_neuron;
    int _forward_neuron_count;
    int _backward_neuron_count;

};

}

#endif  // DONG_NEURON_LAYER_HPP_
