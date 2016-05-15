cmake_minimum_required(VERSION 3.3)
project(GoogleScienceFair)

find_package(OpenCV REQUIRED)
find_package(PythonLibs REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CornerDetector/CornerDetection.cpp LineDetector/line.cpp CornerDetector/CornerDetection.h LineDetector/line.h default.h main.h CornerDetector/CornerCode.h EscapeDetector/EscapeDetection.cpp EscapeDetector/EscapeDetection.h Loging/Loging.h Loging/Loging.cpp CornerDetector/ResultLines.cpp CornerDetector/ResultLines.h
        EscapeDetector/CompareableLine.cpp EscapeDetector/CompareableLine.h EscapeDetector/CompareLine.cpp EscapeDetector/LineMap.cpp EscapeDetector/LineMap.h EscapeDetector/EscapeDetection.cpp EscapeDetector/EscapeDetection.h)

add_executable(GoogleScienceFair ${SOURCE_FILES} )

target_link_libraries(GoogleScienceFair ${OpenCV_LIBS} ${PYTHON_LIBRARIES})
