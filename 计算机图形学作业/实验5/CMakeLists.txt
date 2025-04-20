cmake_minimum_required(VERSION 3.0)
project(liang-berskey-line-clipping)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(liang-berskey-line-clipping liang-berskey-line-clipping.cpp)

# 链接OpenCV库
target_link_libraries(liang-berskey-line-clipping ${OpenCV_LIBS})

