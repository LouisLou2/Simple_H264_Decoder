//
// Created by leo on 24-9-22.
//
#include <algorithm>
#include "entity/nalu/sps_nalu.h"
#include "util/bitstream/bitstream1.h"
#include "const/h264_level_map.h"

// static
std::array<uint8_t,16> SPSNalu::Flat_4X4_16{16};
std::array<uint8_t,16> SPSNalu::Flat_8X8_16{16};


void SPSNalu::scaling_list(
BitStream& bs,
uint8_t* scalingList,
uint8_t sizeOfScalingList,
bool& useDefaultScalingMatrixFlag) {
  uint8_t lastScale = 8;
  uint8_t nextScale = 8;
  for(uint8_t j=0;j<sizeOfScalingList;++j) {
    if(nextScale) {
      uint8_t delta_scale = bs.readSE();
      nextScale = (lastScale + delta_scale + 256) % 256;
      useDefaultScalingMatrixFlag = (j == 0 && nextScale == 0);
    }
    scalingList[j] = (nextScale == 0) ? lastScale : nextScale;
    lastScale = scalingList[j];
  }
}

// TODO: 2017标准中NALU的Header没那么简单了，需要从新书写Header的部分
// 这里data是不包括start code的
SPSNalu::SPSNalu(uint8_t startCodeLen, uint8_t* data, uint32_t size) : Nalu(startCodeLen, data, size) {
  // 委托给父类构造函数之后
  // bit stream从start code和nalu header之后开始
  auto bs1 = BitStream1(rbsp.get(), rbspLen);
  BitStream& bs = bs1;
  profile_idc = bs.readBitN(8);
  constraint_set0_flag = bs.readBit1();
  constraint_set1_flag = bs.readBit1();
  constraint_set2_flag = bs.readBit1();
  constraint_set3_flag = bs.readBit1();
  constraint_set4_flag = bs.readBit1();
  constraint_set5_flag = bs.readBit1();
  reserved_zero_2bits = bs.readBitN(2);
  level_idc = bs.readBitN(8);
  seq_parameter_set_id = bs.readUE();

  if (std::ranges::find(Nalu::specialProfileIdcs.begin(), Nalu::specialProfileIdcs.end(), profile_idc) != Nalu::specialProfileIdcs.end()) {
    uint8_t chroma_format_idc = bs.readUE();
    chroma_format = ChromaFormatUtil::getChromaFormat(chroma_format_idc);
    if (chroma_format == ChromaFormat::YUV444)
      separate_colour_plane_flag = bs.readBit1();
    bit_depth_luma_minus8 = bs.readUE();
    bit_depth_chroma_minus8 = bs.readUE();
    qpprime_y_zero_transform_bypass_flag = bs.readBit1();
    seq_scaling_matrix_present_flag = bs.readBit1();
    if (seq_scaling_matrix_present_flag) {
      for (uint8_t i=0; i < ((chroma_format != ChromaFormat::YUV444)? 8 : 12); ++i) {
        seq_scaling_list_present_flag[i] = bs.readBit1();
        if (seq_scaling_list_present_flag[i]) {
          if (i < 6) {
            scaling_list(bs, ScalingList4x4[i], 16, UseDefaultScalingMatrix4x4Flag[i]);
          } else {
            scaling_list(bs, ScalingList8x8[i-6], 64, UseDefaultScalingMatrix8x8Flag[i-6]);
          }
        }
      }
    }
  }
  log2_max_frame_num_minus4 = bs.readUE();
  pic_order_cnt_type = bs.readUE();
  if (!pic_order_cnt_type) {
    log2_max_pic_order_cnt_lsb_minus4 = bs.readUE();
  } else if (pic_order_cnt_type == 1) {
    delta_pic_order_always_zero_flag = bs.readBit1();
    offset_for_non_ref_pic = bs.readSE();
    offset_for_top_to_bottom_field = bs.readSE();
    num_ref_frames_in_pic_order_cnt_cycle = bs.readUE();
    for (uint8_t i=0; i<num_ref_frames_in_pic_order_cnt_cycle; ++i) {
      offset_for_ref_frame[i] = bs.readSE();
    }
  }
  max_num_ref_frames = bs.readUE();
  gaps_in_frame_num_value_allowed_flag = bs.readBit1();
  pic_width_in_mbs_minus1 = bs.readUE();
  pic_height_in_map_units_minus1 = bs.readUE();
  frame_mbs_only_flag = bs.readBit1();
  if (!frame_mbs_only_flag)
    mb_adaptive_frame_field_flag = bs.readBit1();
  direct_8x8_inference_flag = bs.readBit1();
  frame_cropping_flag = bs.readBit1();
  if (frame_cropping_flag) {
    frame_crop_left_offset = bs.readUE();
    frame_crop_right_offset = bs.readUE();
    frame_crop_top_offset = bs.readUE();
    frame_crop_bottom_offset = bs.readUE();
  }
  vui_parameters_present_flag = bs.readBit1();
  if (vui_parameters_present_flag) {
    // need compute MaxDpsFrames
    MaxDpbFrames = std::min<uint32_t>(
      16,
      H264LevelMap::getMaxDpbMbs(level_idc)/(
        (pic_width_in_mbs_minus1 + 1) * (pic_height_in_map_units_minus1 + 1)
      )
    );
    vui_parameters = VUIParameters(bs, profile_idc, constraint_set3_flag, MaxDpbFrames);
  }
  // 解析完成后，将rbsp中的数据清空
  clearRBSPBuffer();
}

std::string SPSNalu::to_string() const {
  return "It's a SPS Nalu";
}
