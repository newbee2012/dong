#include <iostream>
#include "input_layer.hpp"
using namespace std;

namespace dong
{

InputLayer::InputLayer()
{
}

void InputLayer::forward()
{
    this->_top_data = this->_bottom_data;
}

}
