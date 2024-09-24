//
// Created by leo on 24-9-23.
//
#pragma once
#include <array>
#include <cstdint>

#include "util/bitstream/bitstream.h"

class HRD_PS {
  uint8_t cpb_cnt_minus1; // 0-31
  uint8_t bit_rate_scale;
  uint8_t cpb_size_scale;
  std::array<uint32_t,32> bit_rate_value_minus1{};
  std::array<uint32_t,32> cpb_size_value_minus1{};
  std::array<bool,32> cbr_flag{};
  uint32_t initial_cpb_removal_delay_length_minus1 = 23;
  uint32_t cpb_removal_delay_length_minus1 = 23;
  uint32_t dpb_output_delay_length_minus1 = 23;
  uint32_t time_offset_length = 24;
public:
  explicit HRD_PS(BitStream& bs);
  explicit HRD_PS() = default;
};

