#ifndef DONG_LAYER_HPP_
#define DONG_LAYER_HPP_
#include "common.hpp"
#include "data.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{

enum LayerType {INPUT, DATA, CONVOLUTION};

class Layer
{
public:
    Layer(){};
    virtual ~Layer(){};
    boost::shared_ptr<Data> getBottomData(){return _bottom_data;}
    boost::shared_ptr<Data> getData(){return _data;}
    boost::shared_ptr<Data> getWeight(){return _weight;}
protected:
    boost::shared_ptr<Data> _bottom_data;
    boost::shared_ptr<Data> _data;
    boost::shared_ptr<Data> _weight;
    virtual LayerType getType() = 0;
    //DISABLE_COPY_AND_ASSIGN(Layer);
};

}  // namespace dong

#endif  // DONG_LAYER_HPP_
