cmake_minimum_required(VERSION 2.8)

# use c++ 17
set(CMAKE_CXX_STANDARD 17)

# set project name
project( smart_ptr_ex )

# set include directory
#include_directories( include )

# source files to compile
add_executable( uniquePtrEx
                uniquePtrEx.cpp )