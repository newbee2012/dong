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
    void forward();
    Dtype value;

protected:
    //vector< Neuron<Dtype>* > _forward_neuron;
    //vector< Neuron<Dtype>* > _backward_neuron;
    //vector< Neuron<Dtype>* > _weight;
    int _forward_neuron_count;
    int _backward_neuron_count;

};

}

#endif  // DONG_NEURON_LAYER_HPP_
