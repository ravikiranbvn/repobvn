cmake_minimum_required(VERSION 2.8)

# use c++ 20
set(CMAKE_CXX_STANDARD 20)

# set project name
project( diningPhil )

# set include directory
#include_directories( include )

# source files to compile
add_executable( dp
                src/Philosopher.cpp
                src/main.cpp
                src/Table.cpp)

add_executable( dp_v
                src/Philosopher.cpp
                src/main.cpp
                src/Table.cpp)

target_link_libraries(dp -pthread -Wall -Wextra -Werror -fstack-protector-strong  -fsanitize=thread)

# for valgrind 
target_link_libraries(dp_v -pthread)