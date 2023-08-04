cmake_minimum_required(VERSION 2.8)

# use c++ 17
set(CMAKE_CXX_STANDARD 17)

# set project name
project( SleepingBarber )

# set include directory
#include_directories( include )

# source files to compile
add_executable( sbarber
                src/Barber.cpp
                src/BarberShop.cpp
                src/Customer.cpp
                src/main.cpp )

add_executable( sbarber_v
                src/Barber.cpp
                src/BarberShop.cpp
                src/Customer.cpp
                src/main.cpp )


target_link_libraries(sbarber -pthread -Wall -Wextra -Werror -fstack-protector-strong -fsanitize=thread) 

# for valgrind
target_link_libraries(sbarber_v -pthread)