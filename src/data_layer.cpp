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

void DataLayer::printData()
{
    cout <<"w:"<< _width<<",h:"<<_height<< ",label is " << _label << endl;
    int* p = _data.get();
    for (int w = 0; w < this->_width; w++)
    {
        for (int h = 0; h < this->_height; h++)
        {
            int value = p[w * this->_height+h];
            char x = value!= 0 ? '#' : '.';
            cout << x;
            cout << " ";
        }

        cout << endl;
    }
}

}
