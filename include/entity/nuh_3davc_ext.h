//
// Created by leo on 24-9-24.
//

#ifndef NUH_3DAVC_EXT_H
#define NUH_3DAVC_EXT_H
#include <cstdint>

#include "nuh_svc_ext.h"


struct NUH_3Davc_Ext {
private:
  uint8_t view_idx;
  bool depth_flag;
  bool non_idr_flag;
  uint8_t temporal_id;
  bool anchor_pic_flag;
  bool inter_view_flag;
public:
  NUH_3Davc_Ext() = default;
  explicit NUH_3Davc_Ext(BitStream& bs);
};



#endif //NUH_3DAVC_EXT_H
