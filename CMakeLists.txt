cmake_minimum_required(VERSION 3.28)
project(h264decoder)

set(CMAKE_CXX_STANDARD 23)

add_executable(h264decoder main.cpp
    annexb_reader.cpp
    annexb_reader.h
    nalu.cpp
    nalu.h)
