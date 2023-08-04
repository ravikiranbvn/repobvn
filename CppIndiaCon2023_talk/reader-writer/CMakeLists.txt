cmake_minimum_required(VERSION 2.8)

# use c++ 17
set(CMAKE_CXX_STANDARD 17)

# set project name
project( reader-writer )

# set include directory
#include_directories( include )

# source files to compile
add_executable( rw
                ReaderWriter.cpp)

add_executable( rw_v
                ReaderWriter.cpp)

target_link_libraries(rw -pthread -Wall -Wextra -Werror -fstack-protector-strong -fsanitize=thread)

# for valgrind
target_link_libraries(rw_v -pthread)