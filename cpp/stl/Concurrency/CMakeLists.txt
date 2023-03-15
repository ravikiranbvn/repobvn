cmake_minimum_required(VERSION 2.8)

# use c++ 11
set(CMAKE_CXX_STANDARD 17)

# set project name
project( Concurrency )

# set include directory
#include_directories( include )

#find_package(fmt CONFIG REQUIRED)

# source files to compile
#add_executable( cpp-callback
#                src/main.cpp
#                src/example.cpp )
           
add_executable( atomic_counterEx
                atomic_counterEx.cpp )

add_executable( blocked_queue_OT_error
                blocked_queue_OT_error.cpp )

add_executable( Blocking_bound_q_Ex
                Blocking_bound_q_Ex.cpp )

add_executable( customerToken
                customerToken.cpp )

add_executable( sch
                sch.cpp )

# how to link to a library (OpenCV as example)
# target_link_libraries( cpp-callback ${OpenCV_LIBS} )
#target_link_libraries(packageEx PRIVATE fmt::fmt-header-only) 
