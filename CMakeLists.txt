cmake_minimum_required(VERSION 3.10)
project(test)
set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)

#头文件
include_directories(${EIGEN3_INCLUDE_DIRS} "/home/xxx/myLSH")

#可执行文件
add_executable(testhash main.cpp mylsh.cpp)

