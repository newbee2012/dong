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
    Data(): _num(0),_channels(0),_width(0),_height(0) {}
    explicit Data(const int num, const int channels, const int width, const int height,
                  boost::shared_ptr<int> _data);
    void print();

    int getCount();

protected:
    boost::shared_ptr<int> _data;
    int _num;
    int _channels;
    int _width;
    int _height;

    DISABLE_COPY_AND_ASSIGN(DataLayer);
};

}  // namespace dong

#endif  // DONG_BLOB_HPP_
