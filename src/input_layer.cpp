#include <iostream>
#include "data_layer.hpp"
using namespace std;

namespace dong
{

InputLayer::InputLayer(boost::shared_ptr<Data> data)
{
    this->_data =data;
}



}
