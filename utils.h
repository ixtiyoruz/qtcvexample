#ifndef UTILS_H
#define UTILS_H
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <QDebug>
#include <boost/algorithm/string.hpp>

//here comes global libraries

// executing commands
std::string exec(const char* cmd);
//  struct for camera
struct camera_info{
   std::string name;
   std::string path;
};

// finding cameras from linux using v4l2 ( v4l2 must be installed)
std::vector<camera_info> find_cameras_linux();
#endif // UTILS_H
