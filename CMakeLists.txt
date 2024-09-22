cmake_minimum_required(VERSION 3.28)
project(h264decoder)

set(CMAKE_CXX_STANDARD 23)

add_executable(h264decoder main.cpp
    annexb_reader.cpp
    annexb_reader.h
    nalu.cpp
    nalu.h
    bitstream/bitstream1.cpp
    bitstream/bitstream1.h
    bitstream/bitstream.cpp
    bitstream/bitstream.h
    test/teat_read_nalu.h
    test/test_read_nalu.cpp
    test/test_bitstream.h
    test/test_bitstream.cpp
    util/buf_match.cpp
    util/buf_match.h
    util/mem_insight.cpp
    util/mem_insight.h
)
