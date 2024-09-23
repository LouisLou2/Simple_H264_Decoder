//
// Created by leo on 24-9-23.
//

#include "entity/vui_parameters.h"

VUIParameters::VUIParameters(BitStream& bs, uint8_t profile_idc, bool constraint_set3_flag, uint8_t MaxDpbFrames) {
  aspect_ratio_info_present_flag = bs.readBit1();
  if (aspect_ratio_info_present_flag) {
    uint8_t aspect_ratio_idc = bs.readBitN(8);
    aspect_ratio_enum = SampleAspectRadioUtil::getSampleAspectRadio(aspect_ratio_idc);
    if (aspect_ratio_enum == SampleAspectRadio::Extended_SAR) {
      sar_width = bs.readBitN(16);
      sar_height = bs.readBitN(16);
    }
  }
  overscan_info_present_flag = bs.readBit1();
  if (overscan_info_present_flag) {
    overscan_appropriate_flag = bs.readBit1();
  }
  video_signal_type_present_flag = bs.readBit1();
  if (video_signal_type_present_flag) {
    uint8_t video_format = bs.readBitN(3);
    video_format_enum = VideoFormatUtil::getVideoFormat(video_format);
    video_full_range_flag = bs.readBit1();
    colour_description_present_flag = bs.readBit1();
    if (colour_description_present_flag) {
      uint8_t color_primaries = bs.readBitN(8);
      color_primaries_enum = ColorPrimaryUtil::getColorPrimary(color_primaries);
      uint8_t transfer_characteristics = bs.readBitN(8);
      transfer_characteristics_enum = TransferCharacUtil::getTransferCharac(transfer_characteristics);
      uint8_t matrix_coefficients = bs.readBitN(8);
      matrix_coefficients_enum = MatrixCoefUtil::getMatrixCoefficients(matrix_coefficients);
    }
  }
  chroma_loc_info_present_flag = bs.readBit1();
  if (chroma_loc_info_present_flag) {
    chroma_sample_loc_type_top_field = bs.readUE();
    chroma_sample_loc_type_bottom_field = bs.readUE();
  }
  timing_info_present_flag = bs.readBit1();
  if (timing_info_present_flag) {
    num_units_in_tick = bs.readBitN(32);
    time_scale = bs.readBitN(32);
    fixed_frame_rate_flag = bs.readBit1();
  }
  nal_hrd_parameters_present_flag = bs.readBit1();
  if (nal_hrd_parameters_present_flag) {
    nal_hrd_parameters = HRD_PS(bs);
  }
  vcl_hrd_parameters_present_flag = bs.readBit1();
  if (vcl_hrd_parameters_present_flag) {
    vcl_hrd_parameters = HRD_PS(bs);
  }
  if (nal_hrd_parameters_present_flag || vcl_hrd_parameters_present_flag) {
    low_delay_hrd_flag = bs.readBit1();
  }
  pic_struct_present_flag = bs.readBit1();
  bitstream_restriction_flag = bs.readBit1();
  if (bitstream_restriction_flag) {
    motion_vectors_over_pic_boundaries_flag = bs.readBit1();
    max_bytes_per_pic_denom = bs.readUE();
    max_bits_per_mb_denom = bs.readUE();
    log2_max_mv_length_horizontal = bs.readUE();
    log2_max_mv_length_vertical = bs.readUE();
    num_reorder_frames = bs.readUE();
    max_dec_frame_buffering = bs.readUE();
  }else {
    if (constraint_set3_flag && (profile_idc==44 || profile_idc ==86 || profile_idc == 100 || profile_idc == 110 || profile_idc == 122 || profile_idc == 244) ) {
      num_reorder_frames = 0;
      max_dec_frame_buffering = 0;
    }else {
      num_reorder_frames = MaxDpbFrames;
      max_dec_frame_buffering = MaxDpbFrames;
    }
  }
}
