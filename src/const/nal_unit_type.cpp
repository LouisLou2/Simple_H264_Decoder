//
// Created by leo on 24-9-22.
//

#include "const/nal_unit_type.h"
#include <stdexcept>

NalUnitTypeEnum NalUnitTypeUtil::getNalUnitType(uint8_t nal_unit_type) {
  if (nal_unit_type<=17 || ( 19 <= nal_unit_type && nal_unit_type <= 21)) return static_cast<NalUnitTypeEnum>(nal_unit_type);
  if (nal_unit_type == 18 || nal_unit_type==22 || nal_unit_type==23) return NalUnitTypeEnum::RESERVED;
  if (24 <= nal_unit_type && nal_unit_type <= 31) return NalUnitTypeEnum::UNSPECIFIED;
  throw std::invalid_argument("Invalid nal_unit_type"+std::to_string(nal_unit_type));
}
