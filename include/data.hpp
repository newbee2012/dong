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
    explicit Data(int num, int channels, int width, int height, bool newData);
    Data* setUp(const boost::shared_ptr<int>& data);
    void print();
    int inline count(){return _num*_channels*_width*_height;}

protected:
    boost::shared_ptr<int> _data;
    int _num;
    int _channels;
    int _width;
    int _height;

    DISABLE_COPY_AND_ASSIGN(Data);
};

}  // namespace dong

#endif  // DONG_BLOB_HPP_
