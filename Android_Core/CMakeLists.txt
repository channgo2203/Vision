cmake_minimum_required(VERSION 3.3)
project(Android_Core)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES default.h android_core.cpp android_core.h main.cpp)
set(CORNER_DETECTER CornerDetector/CornerDetection.cpp CornerDetector/CornerDetection.h CornerDetector/CornerCode.h  CornerDetector/ResultLines.cpp CornerDetector/ResultLines.h)
set(LINE_DETECTER LineDetector/line.cpp LineDetector/line.h)
set(ESCAPE_DETECTER EscapeDetector/EscapeDetection.cpp EscapeDetector/EscapeDetection.h EscapeDetector/LineMap.cpp EscapeDetector/LineMap.h EscapeDetector/CompareableLine.cpp EscapeDetector/CompareableLine.h EscapeDetector/CompareLine.cpp)
add_executable(Android_Core ${SOURCE_FILES} ${CORNER_DETECTER} ${LINE_DETECTER} ${ESCAPE_DETECTER})

target_link_libraries(Android_Core ${OpenCV_LIBS})
