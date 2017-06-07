#ifndef DONG_INNER_PRODUCT_LAYER_HPP_
#define DONG_INNER_PRODUCT_LAYER_HPP_
#include "common.hpp"
#include "layer.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>


namespace dong
{
class InnerProductLayer: public Layer
{
public:
    explicit InnerProductLayer();
    virtual LayerType getType()
    {
        return INNER_PRODUCT;
    }
    virtual void setUp(const boost::shared_ptr<Data>& bottomData);
    virtual void init(int num);
    virtual void forward();
    virtual void backward();

protected:
    int _num;

    DISABLE_COPY_AND_ASSIGN(InnerProductLayer);
};

}  // namespace dong

#endif  // DONG_INNER_PRODUCT_LAYER_HPP_
