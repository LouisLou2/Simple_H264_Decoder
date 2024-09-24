//
// Created by leo on 24-9-24.
//

#include "entity/nuh_mvc_ext.h"

NUH_MVC_Ext::NUH_MVC_Ext(BitStream& bs) {
  non_idr_flag = bs.readBit1();
  priority_id = bs.readBitN(6);
  view_id = bs.readBitN(10);
  temporal_id = bs.readBitN(3);
  anchor_pic_flag = bs.readBit1();
  inter_view_flag = bs.readBit1();
  reserved_one_bit = bs.readBit1();
}
