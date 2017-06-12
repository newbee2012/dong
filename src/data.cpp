#ifndef DONG_DATA_HPP_
#define DONG_DATA_HPP_
#include "common.hpp"
#include "data.hpp"
#include "util/gen_bmp.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>
#include <iomanip>
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
        _data.reset(new Neuron<float>[count()]());

        for (int i = 0; i < count(); i++) {
            _data.get()[i].value = 2*((float)random(2)-0.5);// * (random(2)==0?-1:1);
        }

        //int n = MIN(_height,_width);
        //for (int i = 0; i < n; i++)
        //{
        //data[_height/2*_width+_width/2] = 1;
        //}
        //data[0] = 1;
        //data[_height*_width-1] = 1;
        //_data.reset(data);
    }
}

Data* Data::setUp(const boost::shared_ptr< Neuron<float> >& data)
{
    _data = data;
    return this;
}

void Data::print()
{
    cout  << "h:" << _height << ",w:" << _width << endl;

    for (int h = 0; h < _height; h++) {
        for (int w = 0; w < _width; w++) {
            float value = this->get(0, 0, h, w).value;
            //if (value > 0)
            //{
            cout << value;
            //cout << setprecision(2)<<fixed<< value;
            //}
            //else
            //{
            //    cout << ".";
            //}

            if (value < 10) {
                cout << "   ";
            } else if (value < 100) {
                cout << "  ";
            } else {
                cout << " ";
            }
        }

        cout << endl << endl;
    }
}

void Data::genBmp(const char* filename)
{

    RGB* pRGB = new RGB[_width*_height];
    memset(pRGB, 0x0, sizeof(RGB) * _width*_height); // 设置背景为黑色

    for (int h = 0; h < _height; h++) {
        for (int w = 0; w < _width; w++) {
            BYTE gray = this->get(0, 0, h, w).value;
            if(w==0 || w==_width-1|| h==0 ||h==_height-1){
                pRGB[(_height-h-1)*_width+w].r = 0xFF;
                pRGB[(_height-h-1)*_width+w].g = 0xFF;
                pRGB[(_height-h-1)*_width+w].b = 0xFF;
            }else
            {
                pRGB[(_height-h-1)*_width+w].r = gray;
                pRGB[(_height-h-1)*_width+w].g = gray;
                pRGB[(_height-h-1)*_width+w].b = gray;
            }

        }
    }

    BmpTool::generateBMP((BYTE*)pRGB, _width, _height, filename );
}


}  // namespace dong

#endif  // DONG_BLOB_HPP_
