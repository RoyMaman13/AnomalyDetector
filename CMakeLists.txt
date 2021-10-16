cmake_minimum_required(VERSION 3.20)
project(ass1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ass1
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        main.cpp)
