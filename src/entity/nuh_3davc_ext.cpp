//
// Created by leo on 24-9-24.
//

#include "entity/nuh_3davc_ext.h"

NUH_3Davc_Ext::NUH_3Davc_Ext(BitStream& bs) {
  view_idx = bs.readBitN(8);
  depth_flag = bs.readBit1();
  non_idr_flag = bs.readBit1();
  temporal_id = bs.readBitN(3);
  anchor_pic_flag = bs.readBit1();
  inter_view_flag = bs.readBit1();
}
