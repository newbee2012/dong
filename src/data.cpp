#ifndef DONG_DATA_HPP_
#define DONG_DATA_HPP_
#include "common.hpp"
#include "data.hpp"
#include "util/gen_bmp.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>
#include <iomanip>

namespace dong
{
Data::Data(int num, int channels, int height, int width): _num(num), _channels(channels), _height(height),
    _width(width) {};


Data::Data(int num, int channels, int height, int width, InitType type): _num(num), _channels(channels),
    _height(height), _width(width)
{
    _data.reset(new Neuron[count()]);

    for (int i = 0; i < count(); ++i) {
        if (type == Data::CONSTANT) {
            _data[i]._value = 0;
        } else if (type == Data::RANDOM) {
            _data[i]._value = random(2);
        }
    }
}

Data* Data::setUp(const boost::shared_ptr<Neuron[]>& data)
{
    _data = data;
    return this;
}

void Data::print()
{
    cout  << "h:" << _height << ",w:" << _width << endl;

    for (int h = 0; h < _height; h++) {
        for (int w = 0; w < _width; w++) {
            float value = this->get(0, 0, h, w)->_value;
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
    RGB* pRGB = new RGB[_width * _height];
    memset(pRGB, 0x0, sizeof(RGB) * _width * _height); // 设置背景为黑色

    for (int h = 0; h < _height; h++) {
        for (int w = 0; w < _width; w++) {
            BYTE gray = this->get(0, 0, h, w)->_value;

            if (w == 0 || w == _width - 1 || h == 0 || h == _height - 1) {
                pRGB[(_height - h - 1)*_width + w].r = 0xFF;
                pRGB[(_height - h - 1)*_width + w].g = 0xFF;
                pRGB[(_height - h - 1)*_width + w].b = 0xFF;
            } else {
                pRGB[(_height - h - 1)*_width + w].r = gray;
                pRGB[(_height - h - 1)*_width + w].g = gray;
                pRGB[(_height - h - 1)*_width + w].b = gray;
            }
        }
    }

    BmpTool::generateBMP((BYTE*)pRGB, _width, _height, filename );
}


}  // namespace dong

#endif  // DONG_BLOB_HPP_
