#ifndef DONG_DATA_LAYER_HPP_
#define DONG_DATA_LAYER_HPP_
#include "common.hpp"
#include "neuron.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

class Data
{
public:
    enum InitType {CONSTANT, RANDOM,};
    explicit Data(int num, int channels, int height, int width, InitType type);
    explicit Data(int num, int channels, int height, int width);
    Data* setUp(const boost::shared_ptr<Neuron[]>& data);
    void print();
    void printDiff();
    void genBmp(const char* filename, int label);

    int inline count()
    {
        return _num * _channels * _width * _height;
    }

    Neuron* get(int offset)
    {
        return &_data[offset];
    };

    Neuron* get(int n, int c, int h, int w)
    {
        return get(offset(n, c, h, w));
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

    void clearDiff()
    {
        for(int i=0;i < count(); ++i)
        {
            _data[i]._diff = 0.0F;
        }
    }
protected:
    boost::shared_ptr<Neuron[]> _data;
    int _num;
    int _channels;
    int _height;
    int _width;

    DISABLE_COPY_AND_ASSIGN(Data);
};

}  // namespace dong

#endif  // DONG_DATA_LAYER_HPP_
