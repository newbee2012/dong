#include <iostream>
#include <pthread.h>
#include "layer.hpp"
using namespace std;

namespace dong
{
void Layer::forward()
{
    _bottom_data->clearDiff();
    _top_data->clearValue();
    if (_weight_data.get() != NULL)
    {
        _weight_data->clearDiff();
        switch (getType())
        {
        case POOL_LAYER:
        case RELU_LAYER:
        case SOFTMAX_LAYER:
            _weight_data->clearValue();
            break;
        default:
            break;
        }
    }

    this->forward_cpu();
    /*
            cout<<"--------------------"<< EnumNames[getType()]<<" forward-----------------------"<<endl;
            cout<<"bottom data forward"<<endl;
            _bottom_data->print();
            cout<<"top data forward"<<endl;
            _top_data->print();
            cout<<"weight data forward"<<endl;
            if(_weight_data.get()!= NULL)
            {
                _weight_data->print();
            }
    */
}

void Layer::backward()
{
    this->backward_cpu();

    /*
            cout<<"--------------------"<< EnumNames[getType()]<<" backward-----------------------"<<endl;
            cout<<"bottom diff backward"<<endl;
            _bottom_data->printDiff();
            cout<<"weight diff backward"<<endl;
            if(_weight_data.get()!= NULL)
            {
                _weight_data->printDiff();
            }
            else
            {
                cout<<"---------------"<<endl;
            }
    */
}

void Layer::forwardBase()
{
    for (int i = 0; i < _bottom_data->count(); ++i)
    {
        const Neuron* b_neuron = _bottom_data->get(i);

        for (int j = 0; j < b_neuron->_forward_neuron.size(); ++j)
        {
            Neuron* t_neuron = b_neuron->_forward_neuron[j];
            Neuron* w_neuron = b_neuron->_weight_neuron[j];
            t_neuron->_value += (b_neuron->_value * w_neuron->_value);
        }
    }
}

void Layer::backwardBase()
{

    #define THREAD_COUNT 4
    bool multithreading = true;

    if(multithreading)
    {
        pthread_t thread[THREAD_COUNT];
        ThreadParam p[THREAD_COUNT];
        int spilit_count = _bottom_data->count()/THREAD_COUNT;
        for(int i=0; i<THREAD_COUNT; ++i)
        {
            int offset_start = i * spilit_count;
            int offset_end = offset_start + spilit_count;
            if(i== THREAD_COUNT-1)
            {
                offset_end = _bottom_data->count();
            }

            p[i].init(_bottom_data.get(), offset_start, offset_end, i);
            pthread_create(&thread[i], NULL, backwardBase_thread, &p[i]);
        }

        for(int i=0; i<THREAD_COUNT; ++i)
        {
            pthread_join(thread[i], NULL);
        }
    }
    else
    {
        for (int i = 0; i < _bottom_data->count(); ++i)
        {
            Neuron* b_neuron = _bottom_data->get(i);

            for (int j = 0; j < b_neuron->_forward_neuron.size(); ++j)
            {
                Neuron* t_neuron = b_neuron->_forward_neuron[j];
                Neuron* w_neuron = b_neuron->_weight_neuron[j];
                b_neuron->_diff += (t_neuron->_diff * w_neuron->_value);
                w_neuron->_diff += (t_neuron->_diff * b_neuron->_value);
            }
        }
    }

    for (int k = 0; k < _weight_data->count(); ++k)
    {
        Neuron* w_neuron = _weight_data->get(k);

        switch (getType())
        {
        case CONVOLUTION_LAYER:
        case FULL_CONNECT_LAYER:
            w_neuron->_value -= (Layer::BASE_LEARNING_RATE * w_neuron->_diff);
            break;

        default:
            break;
        }
    }
};

void* Layer::backwardBase_thread(void *ptr)
{
    ThreadParam* p = (ThreadParam*)ptr;
    Data* _bottom_data = p->_bottom_data;
    for (int i = p->_offset_start; i < p->_offset_end; ++i)
    {
        Neuron* b_neuron = _bottom_data->get(i);
        for (int j = 0; j < b_neuron->_forward_neuron.size(); ++j)
        {
            Neuron* t_neuron = b_neuron->_forward_neuron[j];
            Neuron* w_neuron = b_neuron->_weight_neuron[j];
            b_neuron->_diff += (t_neuron->_diff * w_neuron->_value);
            w_neuron->_diff += (t_neuron->_diff * b_neuron->_value);
        }
    }

    return 0;
}
}
