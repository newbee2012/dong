#include <iostream>
#include "conv_layer.hpp"
using namespace std;

namespace dong
{

ConvLayer::ConvLayer()
{

}

void ConvLayer::setUp(const boost::shared_ptr<Data>& data){
    this->_bottom_data = data;
}

void ConvLayer::forward(){
}

void ConvLayer::backward(){
}

void ConvLayer::init(int kernel_num, int kernel_channels, int kernel_w, int kernel_h){
    this->_weight.reset(new Data(kernel_num, kernel_channels, kernel_w, kernel_h, true));
}

}
