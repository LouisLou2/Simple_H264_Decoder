//
// Created by leo on 24-9-24.
//

#include "entity/nalu/nalu_header.h"

NaluHeader::NaluHeader(BitStream& bs) {
  forbidden_zero_bit = bs.readBit1();
  nal_ref_idc = bs.readBitN(2);
  uint8_t nal_unit_type = bs.readBitN(5);
  nal_unit_type_enum = NalUnitTypeUtil::getNalUnitType(nal_unit_type);
  if (nal_unit_type == 14 || nal_unit_type == 20 ||
    nal_unit_type == 21) {
    if (nal_unit_type!= 21) {
      svc_extension_flag = bs.readBit1();
    }else {
      avc_3d_extension_flag = bs.readBit1();
    }
    if (svc_extension_flag) {
      svc_ext = NUH_SVC_Ext(bs);
      nuhBytes += 3;
    }else if (avc_3d_extension_flag) {
      avc_3d_ext = NUH_3Davc_Ext(bs);
      nuhBytes += 2;
    }else {
      mvc_ext = NUH_MVC_Ext(bs);
      nuhBytes += 3;
    }
  }
}
