cmake_minimum_required(VERSION 3.3)
project(GoogleScienceFair)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CornerDetector/CornerDetection.cpp CornerDetector/Processing.cpp CornerDetector/line.cpp CornerDetector/CornerDetection.h CornerDetector/Processing.h CornerDetector/line.h CornerDetector/default.h main.h CornerDetector/CornerCode.h)
add_executable(GoogleScienceFair ${SOURCE_FILES})

target_link_libraries(GoogleScienceFair ${OpenCV_LIBS})