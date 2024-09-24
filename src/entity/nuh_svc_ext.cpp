//
// Created by leo on 24-9-24.
//

#include "entity/nuh_svc_ext.h"

NUH_SVC_Ext::NUH_SVC_Ext(BitStream& bs) {
  // begin read
  idr_flag = bs.readBit1();
  priority_id = bs.readBitN(6);
  no_inter_layer_pred_flag = bs.readBit1();
  dependency_id = bs.readBitN(3);
  quality_id = bs.readBitN(4);
  temporal_id = bs.readBitN(3);
  use_ref_base_pic_flag = bs.readBit1();
  discardable_flag = bs.readBit1();
  output_flag = bs.readBit1();
  reserved_three_2bits = bs.readBitN(2);
}
