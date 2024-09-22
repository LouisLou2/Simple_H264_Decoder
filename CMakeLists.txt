cmake_minimum_required(VERSION 3.28)
project(h264decoder)

set(CMAKE_CXX_STANDARD 23)

add_executable(h264decoder main.cpp
    nalu_reader/annexb_reader.cpp
    nalu_reader/annexb_reader.h
    entity/nalu.cpp
    entity/nalu.h
    bitstream/bitstream1.cpp
    bitstream/bitstream1.h
    bitstream/bitstream.h
    test/teat_read_nalu.h
    test/test_read_nalu.cpp
    test/test_bitstream.h
    test/test_bitstream.cpp
    util/buf_match.cpp
    util/buf_match.h
    util/mem_insight.cpp
    util/mem_insight.h
    nalu_reader/nalu_reader.h
    entity/sps_nalu.cpp
    entity/sps_nalu.h
    const/nal_unit_type.cpp
    const/nal_unit_type.h
)
