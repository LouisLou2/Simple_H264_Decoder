//
// Created by leo on 24-9-22.
//

#ifndef SPS_NALU_H
#define SPS_NALU_H
#include <array>

#include "nalu.h"
#include "entity/vui_parameters.h"
#include "bitstream/bitstream.h"
#include "const/chroma_format.h"

class SPSNalu : public Nalu {

  // static
  static std::array<uint8_t,16> Flat_4X4_16;
  static std::array<uint8_t,16> Flat_8X8_16;
  // objectic
  uint8_t profile_idc; // bitstream 遵守的配置
  bool constraint_set0_flag;
  bool constraint_set1_flag;
  bool constraint_set2_flag;
  bool constraint_set3_flag;
  bool constraint_set4_flag;
  bool constraint_set5_flag;
  uint8_t reserved_zero_2bits;
  uint8_t level_idc; // 级别
  uint8_t seq_parameter_set_id; // 序列参数集的唯一标识符， 0-31

  // 色度格式: yuv格式
  ChromaFormat chroma_format = ChromaFormat::YUV420;
  bool separate_colour_plane_flag = false;
  uint8_t bit_depth_luma_minus8 = 0; // 0-6
  uint8_t bit_depth_chroma_minus8 = 0; // 0-6
  bool qpprime_y_zero_transform_bypass_flag = false;

  /*
   * 表示量化矩阵是否存在，0表示不存在，使用系数全为16的默认量化矩阵。
   */
  bool seq_scaling_matrix_present_flag = false;
  // scaling_list_present_flag[ i ] 为true时，表示第i个scaling list的值是有效的
  bool seq_scaling_list_present_flag[12] = {false};

  uint8_t ScalingList4x4[6][16]{};
  uint8_t ScalingList8x8[6][64]{};
  bool UseDefaultScalingMatrix4x4Flag[6]{};
  bool UseDefaultScalingMatrix8x8Flag[6]{};

  uint8_t log2_max_frame_num_minus4;// 0-12
  uint8_t pic_order_cnt_type; // 0-2

  uint8_t log2_max_pic_order_cnt_lsb_minus4 = 0; // 0-12

  bool delta_pic_order_always_zero_flag = false;

  int32_t offset_for_non_ref_pic = 0; // -2^31+1 ~ 2^31-1
  int32_t offset_for_top_to_bottom_field = 0; // -2^31+1 ~ 2^31-1
  uint8_t num_ref_frames_in_pic_order_cnt_cycle = 0;// 0-255

  std::array<int32_t, 256> offset_for_ref_frame{};

  uint32_t max_num_ref_frames;
  bool gaps_in_frame_num_value_allowed_flag;
  uint32_t pic_width_in_mbs_minus1;
  uint32_t pic_height_in_map_units_minus1;
  bool frame_mbs_only_flag;

  bool mb_adaptive_frame_field_flag = false;

  bool direct_8x8_inference_flag;
  bool frame_cropping_flag;

  uint32_t frame_crop_left_offset = 0;
  uint32_t frame_crop_right_offset = 0;
  uint32_t frame_crop_top_offset = 0;
  uint32_t frame_crop_bottom_offset = 0;
  bool vui_parameters_present_flag;
  VUIParameters vui_parameters;

  uint8_t MaxDpbFrames; // 不是文件中读取的，是根据已经解读的数据计算出来，vui_parameters中的最后两个值可能用到
  // func
  static void scaling_list(BitStream& bs, uint8_t* scalingList, uint8_t sizeOfScalingList, bool& useDefaultScalingMatrixFlag);

public:
  // 这里的data是不包括start code的
  SPSNalu(uint8_t startCodeLen, uint8_t* data, uint32_t size);
  [[nodiscard]] std::string to_string() const override;
};



#endif //SPS_NALU_H
