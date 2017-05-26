#ifndef DONG_DATA_LAYER_HPP_
#define DONG_DATA_LAYER_HPP_
#include "common.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

enum LayerType {DATA, CONVOLUTION};

class Layer
{
public:
    Layer(): _num(0),_channels(0),_width(0),_height(0),_pixel_count(0),_label(0) {}
    explicit Layer(const int num, const int channels, const int width, const int height,
                       boost::shared_ptr<Layer> bottom_Layer);
    virtual printData();

    virtual LayerType getType();

protected:
    boost::shared_ptr<Layer> _bottom_Layer;
    boost::shared_ptr<int> _data;
    boost::shared_ptr<int> _weight;
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
