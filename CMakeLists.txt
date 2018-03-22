cmake_minimum_required(VERSION 2.8)
project(GroundTruthLabeler)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES
    *.h
    *.cpp
)
add_executable(GroundTruthLabeler ${SOURCES})
target_link_libraries(GroundTruthLabeler ${OpenCV_LIBS})