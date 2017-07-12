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

    if (_weight_data.get() != NULL) {
        _weight_data->clearDiff();

        switch (getType()) {
        case POOL_LAYER:
        case RELU_LAYER:
        case SOFTMAX_LAYER:
            _weight_data->clearValue();
            break;

        default:
            break;
        }
    }

    if (_bias_data != NULL) {
        _bias_data->clearDiff();
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
    for (int i = 0; i < _bottom_data->count(); ++i) {
        _bottom_data->get(i)->forward();
    }

    if (NULL != _bias_data.get()) {
        for (int i = 0; i < _top_data->count(); ++i) {
            _top_data->get(i)->_value += _bias_data->get(i)->_value;
        }
    }
}

void Layer::backwardBase()
{
#define THREAD_COUNT 4
    bool multithreading = true;

    if (multithreading) {
        pthread_t thread[THREAD_COUNT];
        ThreadParam p[THREAD_COUNT];
        int spilit_count = _bottom_data->count() / THREAD_COUNT;
        for (int i = 0; i < THREAD_COUNT; ++i) {
            int offset_start = i * spilit_count;
            int offset_end = offset_start + spilit_count;
            if (i == THREAD_COUNT - 1) {
                offset_end = _bottom_data->count();
            }

            p[i].init(_bottom_data.get(), offset_start, offset_end, i);
            pthread_create(&thread[i], NULL, backwardBaseThread, &p[i]);
        }

        for (int i = 0; i < THREAD_COUNT; ++i) {
            pthread_join(thread[i], NULL);
        }
    } else {
        Layer::backwardLimit(_bottom_data.get(), 0, _bottom_data->count());
    }

    switch (getType()) {
    case CONVOLUTION_LAYER:
    case FULL_CONNECT_LAYER:
        updateWeight();
        updateBias();
        break;

    default:
        break;
    }
};


void Layer::backwardLimit(Data* bottom_data, int offset_start, int offset_end)
{
    for (int i = offset_start; i < offset_end; ++i) {
        bottom_data->get(i)->backward();
    }
}

void Layer::updateWeight()
{
    for (int i = 0; i < _weight_data->count(); ++i) {
        Neuron* w_neuron = _weight_data->get(i);
        w_neuron->_value -= (Layer::BASE_LEARNING_RATE * w_neuron->_diff);
    }
}

void Layer::updateBias()
{
    for (int i = 0; i < _bias_data->count(); ++i) {
        Neuron* bias_neuron = _bias_data->get(i);
        bias_neuron->_value -= (Layer::BASE_LEARNING_RATE * bias_neuron->_diff);
    }
}

void* Layer::backwardBaseThread(void* ptr)
{
    ThreadParam* p = (ThreadParam*)ptr;
    Data* bottom_data = p->_bottom_data;
    Layer::backwardLimit(bottom_data, p->_offset_start, p->_offset_end);
    return 0;
}
}
