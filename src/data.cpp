#ifndef DONG_DATA_LAYER_HPP_
#define DONG_DATA_LAYER_HPP_
#include "common.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

class Data::Data(const int num, const int channels, const int width, const int height,
                     boost::shared_ptr<int> _data)
{
    this->_num = num;
    this->_channels = channels;
    this->_width=width;
    this->_height=height;
    this->_data = data;
}

void Data::print()
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

int Data::getCount()
{
    return num*channels*width*height;
}


}  // namespace dong

#endif  // DONG_BLOB_HPP_
