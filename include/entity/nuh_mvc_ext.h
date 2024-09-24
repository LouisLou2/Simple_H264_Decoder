//
// Created by leo on 24-9-24.
//

#ifndef NUH_MVC_EXT_H
#define NUH_MVC_EXT_H
#include <cstdint>

#include "util/bitstream/bitstream.h"


struct NUH_MVC_Ext {
private:
  bool non_idr_flag;
  uint8_t priority_id;
  uint16_t view_id;
  uint8_t temporal_id;
  bool anchor_pic_flag;
  bool inter_view_flag;
  bool reserved_one_bit;
public:
  NUH_MVC_Ext() = default;
  explicit NUH_MVC_Ext(BitStream& bs);
};



#endif //NUH_MVC_EXT_H
