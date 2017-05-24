#include <iostream>
#include "data_layer.hpp"
using namespace std;

namespace dong
{

DataLayer::DataLayer(const int num, const int channels, const int height, const int width)
{
    this->_count = num * channels * height * width;
    this->data = new int[num * channels * height * width];
}






}
