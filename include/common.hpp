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

using namespace std;
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <math.h>
#include <algorithm>
#include <float.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define random(x) (rand()%x)
#define BASE_LEARNING_RATE (0.01F)


#endif  // CAFFE_COMMON_HPP_
