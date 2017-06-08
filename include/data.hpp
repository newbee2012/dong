#ifndef DONG_DATA_LAYER_HPP_
#define DONG_DATA_LAYER_HPP_
#include "common.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

class Data
{
public:
    explicit Data(int num, int channels, int height, int width, bool newData);
    Data* setUp(const boost::shared_ptr<float>& data);
    void print();
    void genBmp(const char* filename);

    int inline count()
    {
        return _num * _channels * _width * _height;
    }

    float get(int offset)
    {
        return _data.get()[offset];
    };

    float get(int n, int c, int h, int w)
    {
        return get(offset(n, c, h, w));
    };

    void set(int offset, float value)
    {
        _data.get()[offset] = value;
    };

    void set(int n, int c, int h, int w, float value)
    {
        _data.get()[offset(n, c, h, w)] = value;
    };

    inline int offset(const int n, const int c = 0, const int h = 0, const int w = 0) const
    {
        return ((n * channels() + c) * height() + h) * width() + w;
    }

    inline int num() const
    {
        return _num;
    }

    inline int channels() const
    {
        return _channels;
    }

    inline int height() const
    {
        return _height;
    }

    inline int width() const
    {
        return _width;
    }
protected:
    boost::shared_ptr<float> _data;
    int _num;
    int _channels;
    int _width;
    int _height;

    DISABLE_COPY_AND_ASSIGN(Data);
};

}  // namespace dong

#endif  // DONG_BLOB_HPP_
