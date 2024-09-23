cmake_minimum_required(VERSION 3.28)
project(h264decoder)

set(CMAKE_CXX_STANDARD 23)

# add include path
include_directories("include")

set(PROJ_RELATE_INCLUDE_DIR "include")
set(PROJ_RELATE_SRC_DIR "src")

add_executable(h264decoder main.cpp
    ${PROJ_RELATE_SRC_DIR}/codec/nalu_reader/annexb_reader.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/codec/nalu_reader/annexb_reader.h
    ${PROJ_RELATE_SRC_DIR}/entity/nalu.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/entity/nalu.h
    ${PROJ_RELATE_SRC_DIR}/bitstream/bitstream1.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/bitstream/bitstream1.h
    ${PROJ_RELATE_INCLUDE_DIR}/bitstream/bitstream.h
    ${PROJ_RELATE_INCLUDE_DIR}/test/teat_read_nalu.h
    ${PROJ_RELATE_SRC_DIR}/test/test_read_nalu.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/test/test_bitstream.h
    ${PROJ_RELATE_SRC_DIR}/test/test_bitstream.cpp
    ${PROJ_RELATE_SRC_DIR}/util/buf_match.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/util/buf_match.h
    ${PROJ_RELATE_SRC_DIR}/util/mem_insight.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/util/mem_insight.h
    ${PROJ_RELATE_INCLUDE_DIR}/codec/nalu_reader/nalu_reader.h
    ${PROJ_RELATE_SRC_DIR}/entity/sps_nalu.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/entity/sps_nalu.h
    ${PROJ_RELATE_SRC_DIR}/const/nal_unit_type.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/const/nal_unit_type.h
    ${PROJ_RELATE_SRC_DIR}/codec/data_filter.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/codec/data_filter.h
    ${PROJ_RELATE_INCLUDE_DIR}/const/chroma_format.h
    ${PROJ_RELATE_SRC_DIR}/entity/vui_parameters.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/entity/vui_parameters.h
    ${PROJ_RELATE_INCLUDE_DIR}/const/sample_aspect_radio.h
    ${PROJ_RELATE_INCLUDE_DIR}/const/video_format.h
    ${PROJ_RELATE_SRC_DIR}/const/color_primary.cpp
    ${PROJ_RELATE_INCLUDE_DIR}/const/color_primary.h
    ${PROJ_RELATE_INCLUDE_DIR}/const/transfer_charac.h
    include/const/matrix_coefficients.h
    src/entity/hrd_ps.cpp
    include/entity/hrd_ps.h
    include/const/h264_level_map.h
    src/entity/level_limits.cpp
    include/entity/level_limits.h
    src/const/h264_level_map.cpp
)
