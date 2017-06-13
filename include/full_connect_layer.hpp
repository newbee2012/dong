#ifndef DONG_FULL_CONNECT_LAYER_HPP_
#define DONG_FULL_CONNECT_LAYER_HPP_
#include "common.hpp"
#include "layer.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
class FullConnectLayer: public Layer
{
public:
    explicit FullConnectLayer(){_forwardType = INNER_PRODUCT;};
    virtual LayerType getType(){return FULL_CONNECT;}
    virtual void setUp(const boost::shared_ptr<Data>& bottomData);
    virtual void init(int num);
    virtual void forward_cpu();
    virtual void backward();

protected:
    int _num;

    DISABLE_COPY_AND_ASSIGN(FullConnectLayer);
};

}  // namespace dong

#endif  // DONG_FULL_CONNECT_LAYER_HPP_
