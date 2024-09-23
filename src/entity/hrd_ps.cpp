//
// Created by leo on 24-9-23.
//

#include "entity/hrd_ps.h"

HRD_PS::HRD_PS(BitStream& bs) {
  cpb_cnt_minus1 = bs.readUE();
  bit_rate_scale = bs.readBitN(4);
  cpb_size_scale = bs.readBitN(4);
  for (int i = 0; i <= cpb_cnt_minus1; ++i) {
    bit_rate_value_minus1[i] = bs.readUE();
    cpb_size_value_minus1[i] = bs.readUE();
    cbr_flag[i] = bs.readBit1();
  }
  initial_cpb_removal_delay_length_minus1 = bs.readBitN(5);
  cpb_removal_delay_length_minus1 = bs.readBitN(5);
  dpb_output_delay_length_minus1 = bs.readBitN(5);
  time_offset_length = bs.readBitN(5);
}
