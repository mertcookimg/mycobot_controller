#ifndef _MYCOBOT_COMMON_HH_
#define _MYCOBOT_COMMON_HH_

#include <string>
#include <map>
#include <vector>

namespace mycobot_controller
{
    typedef std::vector<double> DoubleArray;
    typedef std::vector<std::string> StringArray;
    static const int NUM_JOINT = 6;
    static const double TIME_PERIOD=0.05;
};

#endif // _MYCOBOT_COMMON_HH_