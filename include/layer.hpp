#ifndef DONG_LAYER_HPP_
#define DONG_LAYER_HPP_
#include "common.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

enum LayerType {DATA, CONVOLUTION};

class Layer
{
public:
    explicit Layer(){};
    virtual LayerType getType();
    boost::shared_ptr<Data> getBottomData(){return _bottom_data};
    boost::shared_ptr<Data> getData(){return _data};
    boost::shared_ptr<Data> getWeight();
protected:
    boost::shared_ptr<Data> _bottom_data;
    boost::shared_ptr<Data> _data;
    boost::shared_ptr<Data> _weight;
    DISABLE_COPY_AND_ASSIGN(Layer);
};

}  // namespace dong

#endif  // DONG_LAYER_HPP_
