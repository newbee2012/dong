#include <iostream>
#include "input_layer.hpp"
using namespace std;

namespace dong
{

InputLayer::InputLayer()
{
}
void InputLayer::setUp(const boost::shared_ptr<Data>& data)
{
    Layer::setUp(data);
    this->_top_data = this->_bottom_data;
}

void InputLayer::forward_cpu()
{
}

void InputLayer::backward_cpu()
{
}


}
