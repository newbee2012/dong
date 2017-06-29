#ifndef CAFFE_COMMON_HPP_
#define CAFFE_COMMON_HPP_

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned int  DWORD;
typedef int    INT32;
// Disable the copy and assignment operator for a class.
#define DISABLE_COPY_AND_ASSIGN(classname) \
private:\
  classname(const classname&);\
  classname& operator=(const classname&)


#include <gflags/gflags.h>
#include <glog/logging.h>
#include <math.h>
#include <algorithm>
#include <float.h>
#include <boost/math/special_functions/next.hpp>
#include <boost/random.hpp>
#include <boost/shared_ptr.hpp>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define random(x) (rand()%x)
#define BASE_LEARNING_RATE (0.001F)


using namespace std;
using namespace boost;

namespace dong
{

using namespace dong;
typedef boost::mt19937 rng_t;


class RNG
{
public:
    RNG();
    explicit RNG(unsigned int seed);
    explicit RNG(const RNG&);
    RNG& operator=(const RNG&);
    void* generator();
private:
    class Generator;
    shared_ptr<Generator> generator_;
};


class MathUtils
{
public:

    static shared_ptr<RNG> random_generator_;

    static RNG& rng_stream()
    {
        if (!random_generator_)
        {
            random_generator_.reset(new RNG());
        }

        return *(random_generator_);
    }

    static float caffe_nextafter(const float b)
    {
        return boost::math::nextafter<float>(b, std::numeric_limits<float>::max());
    }


    static void caffe_rng_uniform(const int n, const float a, const float b, float* r)
    {
        rng_t engine;
        boost::uniform_real<float> random_distribution(a, caffe_nextafter(b));
        boost::variate_generator<dong::rng_t*, boost::uniform_real<float> > my_generator(&engine, random_distribution);

        for (int i = 0; i < n; ++i)
        {
            r[i] = my_generator();
        }
    }


};


}

#endif  // CAFFE_COMMON_HPP_
