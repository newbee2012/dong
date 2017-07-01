#ifndef DONG_COMMON_HPP_
#define DONG_COMMON_HPP_

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

using namespace std;
using namespace boost;

#endif  // DONG_COMMON_HPP_
