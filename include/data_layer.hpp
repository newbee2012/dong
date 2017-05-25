#ifndef DONG_DATA_LAYER_HPP_
#define DONG_DATA_LAYER_HPP_
#include "common.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
class DataLayer
{
public:
    DataLayer(): _num(0),_channels(0),_width(0),_height(0),_pixel_count(0),_label(0) {}
    explicit DataLayer(const int num, const int channels, const int width, const int height,
                       const int label,boost::shared_ptr<int> data);
    void printData();

protected:
    boost::shared_ptr<int> _data;
    int _num;
    int _channels;
    int _width;
    int _height;
    int _pixel_count;
    int _label;

    DISABLE_COPY_AND_ASSIGN(DataLayer);
};

}  // namespace dong

#endif  // DONG_BLOB_HPP_
