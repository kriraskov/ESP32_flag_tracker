cmake_minimum_required(VERSION 3.24)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ESP32_flag_accel)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(src)