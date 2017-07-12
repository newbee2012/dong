#ifndef DONG_DATA_HPP_
#define DONG_DATA_HPP_
#include "common.hpp"
#include "data.hpp"
#include "util/gen_bmp.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>
#include <iomanip>
#include "util/math_utils.hpp"

namespace dong
{
Data::Data(int num, int channels, int height, int width): _num(num), _channels(channels), _height(height),
    _width(width) {};


Data::Data(int num, int channels, int height, int width, InitType type): _num(num), _channels(channels),
    _height(height), _width(width)
{
    _neurons.reset(new Neuron[count()]);
    int fan_in = count() / num;
    int fan_out = count() / channels;
    float n = (fan_in + fan_out) / float(2);
    float scale = sqrt(float(3) / n);
    float* t = new float[count()];
    RandomGenerator::rng_uniform(count(), -scale, scale, t);
    for (int i = 0; i < count(); ++i) {
        if (type == Data::CONSTANT) {
            _neurons[i]._value = 0.0F;
        } else if (type == Data::RANDOM) {
            _neurons[i]._value = ((float)random(2) - 0.5);
            _neurons[i]._value /= 1000;
        } else if (type == Data::XAVIER) {
            _neurons[i]._value = t[i];
        }

        _neurons[i]._diff = 0.0F;
    }

    delete[] t;
}

void Data::clearDiff()
{
    for (int i = 0; i < count(); ++i) {
        _neurons[i]._diff = 0.0F;
    }
}

void Data::clearValue()
{
    for (int i = 0; i < count(); ++i) {
        _neurons[i]._value = 0.0F;
    }
}

void Data::setUp(const boost::shared_ptr<Neuron[]>& neurons)
{
    _neurons = neurons;
}

void Data::print()
{
    cout  << "h:" << _height << ",w:" << _width << endl;

    for (int n = 0; n < _num; n++) {
        for (int c = 0; c < _channels; c++) {
            for (int h = 0; h < _height; h++) {
                for (int w = 0; w < _width; w++) {
                    float value = this->get(n, c, h, w)->_value;
                    cout << value;

                    //cout << setprecision(2)<<fixed<< value;
                    if (value < 10) {
                        cout << "   ";
                    } else if (value < 100) {
                        cout << "  ";
                    } else {
                        cout << " ";
                    }
                }

                if (_width > 1) {
                    cout << endl << endl;
                }
            }

            cout << "----------------------------------" << endl;
        }
    }
}

void Data::printDiff()
{
    for (int n = 0; n < _num; n++) {
        for (int c = 0; c < _channels; c++) {
            for (int h = 0; h < _height; h++) {
                for (int w = 0; w < _width; w++) {
                    float value = this->get(n, c, h, w)->_diff;
                    cout << value;

                    //cout << setprecision(2)<<fixed<< value;
                    if (value < 10) {
                        cout << "   ";
                    } else if (value < 100) {
                        cout << "  ";
                    } else {
                        cout << " ";
                    }
                }

                if (_width > 1) {
                    cout << endl << endl;
                }
            }

            cout << "----------------------------------" << endl;
        }
    }
}

void Data::genBmp(const char* format, int index)
{
    for (int n = 0; n < _num; n++) {
        char filename[60];
        snprintf(filename, sizeof(filename), format, index, n);
        RGB* pRGB = new RGB[_width * _height];
        memset(pRGB, 0x0, sizeof(RGB) * _width * _height); // 设置背景为黑色

        for (int h = 0; h < _height; h++) {
            for (int w = 0; w < _width; w++) {
                BYTE gray = this->get(n, 0, h, w)->_value > 1 ? this->get(n, 0, h, w)->_value : (this->get(n, 0, h,
                            w)->_value) * 0xFF * 10;

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

        BmpTool::generateBMP((BYTE*)pRGB, _width, _height, filename);
    }
}


}  // namespace dong

#endif  // DONG_BLOB_HPP_
