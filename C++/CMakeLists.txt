cmake_minimum_required(VERSION 3.3)
project(SidewalkDetection)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp main.h default.h cluster.cpp cluster.h color.cpp color.h line.cpp line.h ConerDetection.cpp ConerDetection.h Processing.cpp Processing.h)
add_executable(SidewalkDetection ${SOURCE_FILES} cluster.cpp color.cpp color.h line.cpp line.h)

target_link_libraries(SidewalkDetection ${OpenCV_LIBS})
