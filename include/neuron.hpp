#ifndef DONG_NEURON_LAYER_HPP_
#define DONG_NEURON_LAYER_HPP_
#include "common.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

template <typename Dtype> class Neuron
{
public:
    Neuron(){};
    void forward()
    {
        for(int i = 0; i < _forward_neuron_count; ++i)
        {
            _forward_neuron[i]->value += (value * _weight[i]->value);
        }
    }

protected:
    vector< Neuron<Dtype>* > _forward_neuron;
    vector< Neuron<Dtype>* > _backward_neuron;
    vector< Neuron<Dtype>* > _weight;
    int _forward_neuron_count;
    int _backward_neuron_count;
    Dtype value;
};

}

#endif  // DONG_NEURON_LAYER_HPP_
