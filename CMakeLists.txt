cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib)

project(OpenCV_Base)

# OpenCV config
set(OpenCV_INCLUDE_DIRS /usr/local/opencv_3.4.18/include)
set(OpenCV_LIBS /usr/local/opencv_3.4.18/lib)

add_subdirectory(src)
