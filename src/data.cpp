#ifndef DONG_DATA_HPP_
#define DONG_DATA_HPP_
#include "common.hpp"
#include "data.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>

#define random(x) (rand()%x)

namespace dong
{

Data::Data(int num, int channels, int height, int width, bool newData)
{
    this->_num = num;
    this->_channels = channels;
    this->_height = height;
    this->_width = width;
    if (newData) {
        int* data = new int[count()]();
        for(int i=0;i < count();i++)
        {
            data[i] = random(2);
        }
        _data.reset(data);
    }
}

Data* Data::setUp(const boost::shared_ptr<int>& data)
{
    _data = data;
    return this;
}

void Data::print()
{
    cout << "w:" << _width << ",h:" << _height << endl;
    int* p = _data.get();

    for (int w = 0; w < this->_width; w++) {
        for (int h = 0; h < this->_height; h++) {
            int value = p[w * this->_height + h];
            if(value>0)
            {
                cout << value;
            }
            else
            {
                cout << ".";
            }

            if(value<10)
            {
                cout << "   ";
            }
            else
            {
                cout << "  ";
            }

        }

        cout << endl<<endl;
    }
}


}  // namespace dong

#endif  // DONG_BLOB_HPP_
