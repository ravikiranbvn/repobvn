cmake_minimum_required(VERSION 2.8)

# use c++ 11
set(CMAKE_CXX_STANDARD 20)

# set project name
project( smart_ptr_ex )

# set include directory
#include_directories( include )

# source files to compile
add_executable( uniquePtrEx
                uniquePtrEx.cpp )