cmake_minimum_required (VERSION 2.8)

project (HRTimerpp)

set (HRTimerpp_VERSION_MAJOR 0)
set (HRTimerpp_VERSION_MINOR 2)
set (HRTimerpp_VERSION_PATCH 0)

add_definitions ("-Wall -Wextra -pedantic -std=c++11")

add_subdirectory (src)
