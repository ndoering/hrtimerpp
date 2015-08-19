cmake_minimum_required (VERSION 2.8)

project (HRTimerpp CXX)

set (VERSION_MAJOR  "0")
set (VERSION        "0.4.2")

include(CheckCXXCompilerFlag)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DNO_CXX14")
else()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no
    C++14 or C++11 support.")
endif()

add_subdirectory (src)
