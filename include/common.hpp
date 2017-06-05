#ifndef CAFFE_COMMON_HPP_
#define CAFFE_COMMON_HPP_

// Disable the copy and assignment operator for a class.
#define DISABLE_COPY_AND_ASSIGN(classname) \
private:\
  classname(const classname&);\
  classname& operator=(const classname&)

using namespace std;
#include <gflags/gflags.h>
#include <glog/logging.h>

#endif  // CAFFE_COMMON_HPP_
