cmake_minimum_required(VERSION 2.8)

# use c++ 17
set(CMAKE_CXX_STANDARD 17)

# set project name
project( reactorPattern )

# set include directory
#include_directories( include )
# source files to compile

#--------------------------
add_executable( closeexsem
                CloseExSem.cpp)

add_executable( closeexsem_v
                CloseExSem.cpp)

target_link_libraries(closeexsem -pthread -Wall -Wextra -Werror -luv -fstack-protector-strong -fsanitize=thread)

# for valgrind
target_link_libraries(closeexsem_v -pthread -luv)


#--------------------------
add_executable( closeexprom
                CloseExProm.cpp)

add_executable( closeexprom_v
                CloseExProm.cpp)

target_link_libraries(closeexprom -pthread -Wall -Wextra -Werror -luv -fstack-protector-strong -fsanitize=thread)

# for valgrind
target_link_libraries(closeexprom_v -pthread -luv)

#--------------------------
add_executable( asyncuv
                UvAsyncEx.cpp)

add_executable( asyncuv_v
                UvAsyncEx.cpp)

target_link_libraries(asyncuv -pthread -Wall -Wextra -Werror -luv -fstack-protector-strong -fsanitize=thread)

# for valgrind
target_link_libraries(asyncuv_v -pthread -luv)
