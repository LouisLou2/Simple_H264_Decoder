//
// Created by leo on 24-9-24.
//

#ifndef NALU_HEADER_H
#define NALU_HEADER_H
#include <cstdint>

#include "entity/nuh_3davc_ext.h"
#include "entity/nuh_mvc_ext.h"
#include "entity/nuh_svc_ext.h"
#include "util/bitstream/bitstream.h"
#include "const/nal_unit_type.h"


struct NaluHeader {
  friend class Nalu;
  friend class AUDNalu;
private:
  bool forbidden_zero_bit;
  int8_t nal_ref_idc;
  NalUnitTypeEnum nal_unit_type_enum; // // 5 bits, indicating the type of the NAL unit
  bool svc_extension_flag = false;
  bool avc_3d_extension_flag = false;
  NUH_SVC_Ext svc_ext{};
  NUH_3Davc_Ext avc_3d_ext{};
  NUH_MVC_Ext mvc_ext{};
  // self defined
  uint8_t nuhBytes = 1;
public:
  NaluHeader() = default;
  explicit NaluHeader(BitStream& bs);
};



#endif //NALU_HEADER_H
