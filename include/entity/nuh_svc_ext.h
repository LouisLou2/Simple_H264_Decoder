//
// Created by leo on 24-9-24.
//

#ifndef NNH_SVC_EXT_H
#define NNH_SVC_EXT_H
#include <cstdint>

#include "bitstream/bitstream.h"


// nal_unit_svc_extension
struct NUH_SVC_Ext {
private:
  bool idr_flag;
  uint8_t priority_id;
  bool no_inter_layer_pred_flag;
  uint8_t dependency_id;
  uint8_t quality_id;
  uint8_t temporal_id;
  bool use_ref_base_pic_flag;
  bool discardable_flag;
  bool output_flag;
  uint8_t reserved_three_2bits;
public:
  NUH_SVC_Ext() = default;
  explicit NUH_SVC_Ext(BitStream& bs);
};



#endif //NNH_SVC_EXT_H
