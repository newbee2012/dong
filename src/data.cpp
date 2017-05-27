#ifndef DONG_DATA_HPP_
#define DONG_DATA_HPP_
#include "common.hpp"
#include "data.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

Data::Data(int num, int channels, int width, int height, bool newData)
{
    this->_num = num;
    this->_channels = channels;
    this->_width=width;
    this->_height=height;
    if(newData)
    {
        _data.reset(new int[count()]);
    }

}

Data* Data::setUp(const boost::shared_ptr<int>& data)
{
    _data = data;
    return this;
}

void Data::print()
{
    cout <<"w:"<< _width<<",h:"<<_height<< endl;
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


}  // namespace dong

#endif  // DONG_BLOB_HPP_
