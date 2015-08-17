cmake_minimum_required (VERSION 2.8)

project (HRTimerpp)

set (VERSION_MAJOR  "0")
set (VERSION        "0.4.1")

add_definitions ("-Wall -Wextra -pedantic -std=c++14")

add_subdirectory (src)
