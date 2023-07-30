cmake_minimum_required(VERSION 2.8)

# use c++ 17
set(CMAKE_CXX_STANDARD 17)

# set project name
project( dsa_cpp_ex )

# set include directory
#include_directories( include )

# source files to compile
add_executable( minStack
                MinStack.cpp )

# how to link to a library (OpenCV as example)
# target_link_libraries( cpp-callback ${OpenCV_LIBS} )
#target_link_libraries(packageEx PRIVATE fmt::fmt-header-only) 