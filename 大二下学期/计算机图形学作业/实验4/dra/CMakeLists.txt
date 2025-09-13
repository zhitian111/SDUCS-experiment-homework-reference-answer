cmake_minimum_required(VERSION 3.0)
project(line)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(line line.cpp)

# 链接OpenCV库
target_link_libraries(line ${OpenCV_LIBS})

