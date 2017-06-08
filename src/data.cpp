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

    if (newData)
    {
        float* data = new float[count()]();
        for (int i = 0; i < count(); i++)
        {
            data[i] = random(2) * (random(2)==0?-1:1);
        }

        int n = MIN(_height,_width);
        //for (int i = 0; i < n; i++)
        //{
            //data[_height/2*_width+_width/2] = 1;
        //}

        //data[0] = 1;
        //data[_height*_width-1] = 1;
        _data.reset(data);
    }
}

Data* Data::setUp(const boost::shared_ptr<float>& data)
{
    _data = data;
    return this;
}

void Data::print()
{
    cout  << "h:" << _height << ",w:" << _width << endl;
    for (int h = 0; h < _height; h++)
    {
        for (int w = 0; w < _width; w++)
        {
            float value = this->get(0,0,h,w);
            //if (value > 0)
            //{
                cout << value;
            //}
            //else
            //{
            //    cout << ".";
            //}

            if (value < 10)
            {
                cout << "   ";
            }
            else if (value < 100)
            {
                cout << "  ";
            }
            else
            {
                cout << " ";
            }

        }

        cout << endl << endl;
    }
}


}  // namespace dong

#endif  // DONG_BLOB_HPP_
