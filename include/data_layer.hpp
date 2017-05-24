#ifndef DONG_DATA_LAYER_HPP_
#define DONG_DATA_LAYER_HPP_
#include "common.hpp"
#include <vector>


namespace dong
{
class DataLayer
{
public:
    DataLayer(): _count(0) {}
    explicit DataLayer(const int num, const int channels, const int height,
                       const int width);

protected:
    int* data;
    int _count;

    DISABLE_COPY_AND_ASSIGN(DataLayer);
};

}  // namespace dong

#endif  // DONG_BLOB_HPP_
