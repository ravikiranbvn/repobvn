cmake_minimum_required(VERSION 2.8)

# use c++ 11
set(CMAKE_CXX_STANDARD 20)

# set project name
project( vs_cpp_ex_ )

# set include directory
#include_directories( include )

# source files to compile
add_executable( assignOp
                assignOp.cpp )

add_executable( bitWiseOp
                bitWiseOp.cpp)

add_executable( cbEx
                cbEx.cpp)

add_executable( cToCppEx
                cToCppEx.cpp )

add_executable( complexMapEx
                complexMapEx.cpp )

add_executable ( dequeEx
                 dequeEx.cpp )

#add_executable( evenOdd
#                 evenOdd.cpp)

add_executable( generic_msg
                generic_msg.cpp )

add_executable( joinstringsEx
                joinstringsEx.cpp)

add_executable( lamdaEx
                lamdaEx.cpp)

add_executable( lamdaEx2
                lamdaEx2.cpp)

add_executable( memBlockEx 
                memBlockEx.cpp)

add_executable( moveConst
                moveConst.cpp )

add_executable( mvEx
                mvEx.cpp )
                
add_executable( packageEx 
                packageEx.cpp)

add_executable( reverseStr
                reverseStr.cpp )

add_executable( shallowVsDeepCpy
                shallowVsDeepCpy.cpp )

add_executable( shallowVsDeepSwap
                shallowVsDeepSwap.cpp )

add_executable ( strongTypeEx
                 strongTypeEx.cpp )

add_executable( strRecplaceEx
                strReplaceEx.cpp )

add_executable( stuEx
                stuEx.cpp )

add_executable( tempEx2
                tempEx2.cpp )
                
add_executable( templateEx
                templateEx.cpp )

add_executable( test 
                test.cpp)

add_executable( val_isbn13
                val_isbn13.cpp)

add_executable( vectorEx
                vectorEx.cpp)

# how to link to a library (OpenCV as example)
# target_link_libraries( cpp-callback ${OpenCV_LIBS} )
#target_link_libraries(packageEx PRIVATE fmt::fmt-header-only) 