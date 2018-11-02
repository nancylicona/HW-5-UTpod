cmake_minimum_required(VERSION 3.12)
project(HW_5_UTpod)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW_5_UTpod
        driver.cpp
        Song.cpp
        Song.h
        UtPod.cpp
        UtPod.h)
