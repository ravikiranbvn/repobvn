cmake_minimum_required(VERSION 2.8)

# use c++ 11
set(CMAKE_CXX_STANDARD 17)

# set project name
project( vs_cpp_ex_ )

# set include directory
#include_directories( include )

find_package(fmt CONFIG REQUIRED)

# source files to compile
#add_executable( cpp-callback
#                src/main.cpp
#                src/example.cpp )
           
add_executable( shallowVsDeepCpy
                shallowVsDeepCpy.cpp )

add_executable( shallowVsDeepSwap
                shallowVsDeepSwap.cpp )

add_executable( assignOp
                assignOp.cpp )

add_executable( moveConst
                moveConst.cpp )

add_executable( stdmoveConst
                stdmoveConst.cpp )

add_executable( test
                test.cpp )

add_executable( packageEx 
                packageEx.cpp)

add_executable( memBlockEx 
                memBlockEx.cpp)

add_executable( templateEx 
                templateEx.cpp)

add_executable( lamdaEx
                lamdaEx.cpp)
# how to link to a library (OpenCV as example)
# target_link_libraries( cpp-callback ${OpenCV_LIBS} )
target_link_libraries(packageEx PRIVATE fmt::fmt-header-only) 