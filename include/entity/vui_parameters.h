//
// Created by leo on 24-9-23.
//

#ifndef VUI_PARAMETERS_H
#define VUI_PARAMETERS_H
#include <cstdint>

#include "hrd_ps.h"
#include "const/color_primary.h"
#include "const/matrix_coefficients.h"
#include "const/sample_aspect_radio.h"
#include "const/transfer_charac.h"
#include "const/video_format.h"

// 为了性能考虑，成员就先设置公有吧
class VUIParameters {
  bool aspect_ratio_info_present_flag;
  SampleAspectRadio aspect_ratio_enum = SampleAspectRadio::Unspecified;
  uint16_t sar_width = 0;
  uint16_t sar_height = 0;
  bool overscan_info_present_flag;
  bool overscan_appropriate_flag = true; // 标准上没有默认值，这里设置为true， 此标志貌似没大用处
  bool video_signal_type_present_flag;
  VideoFormatEnum video_format_enum = VideoFormatEnum::Unspecified;
  bool video_full_range_flag = false;
  bool colour_description_present_flag = false; // 标准上没有默认值
  ColorPrimaryEnum color_primaries_enum = ColorPrimaryEnum::Unspecified;
  TransferCharacEnum transfer_characteristics_enum = TransferCharacEnum::Unspecified;
  MatrixCoefEnum matrix_coefficients_enum = MatrixCoefEnum::Unspecified;
  bool chroma_loc_info_present_flag;
  uint8_t chroma_sample_loc_type_top_field = 0; // 0-5
  uint8_t chroma_sample_loc_type_bottom_field = 0; // 0-5
  bool timing_info_present_flag;
  uint32_t num_units_in_tick = 0;
  uint32_t time_scale = 0;
  bool fixed_frame_rate_flag = false;
  bool nal_hrd_parameters_present_flag;
  HRD_PS nal_hrd_parameters;
  bool vcl_hrd_parameters_present_flag;
  HRD_PS vcl_hrd_parameters;
  bool low_delay_hrd_flag = true;
  bool pic_struct_present_flag = false;
  bool bitstream_restriction_flag;
  bool motion_vectors_over_pic_boundaries_flag = true;
  uint8_t max_bytes_per_pic_denom = 2; // 0-16
  uint8_t max_bits_per_mb_denom = 1; // 0-16
  uint8_t log2_max_mv_length_horizontal = 15; // 0-15
  uint8_t log2_max_mv_length_vertical = 15; // 0-15
  uint32_t num_reorder_frames;
  uint32_t max_dec_frame_buffering;

public:
  VUIParameters(BitStream&bs,uint8_t profile_idc,  bool constraint_set3_flag, uint8_t MaxDpbFrames);
  VUIParameters() = default;
};



#endif //VUI_PARAMETERS_H
