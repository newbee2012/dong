#include <iostream>
#include "data_layer.hpp"
using namespace std;

namespace dong
{

DataLayer::DataLayer(const int num, const int channels, const int width,const int height, const int label,
                     boost::shared_ptr<int> data)
{
    this->_num = num;
    this->_channels = channels;
    this->_width=width;
    this->_height=height;
    this->_label = label;
    this->_data = data;
    this->_pixel_count = num * channels * height * width;
}



}
