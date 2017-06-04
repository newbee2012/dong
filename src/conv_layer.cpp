#include <iostream>
#include "conv_layer.hpp"
using namespace std;

namespace dong
{

ConvLayer::ConvLayer(const boost::shared_ptr<Data>& bottomData)
{
    this->_bottom_data = bottomData;
}



}
