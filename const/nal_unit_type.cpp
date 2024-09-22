//
// Created by leo on 24-9-22.
//

#include "nal_unit_type.h"
#include <stdexcept>

NalUnitTypeEnum NalUnitTypeUtil::getNalUnitType(uint8_t nal_unit_type) {
  switch (nal_unit_type) {
    case 1:
      return NalUnitTypeEnum::CODED_SLICE_NON_IDR;
    case 2:
      return NalUnitTypeEnum::CODED_SLICE_DPA;
    case 3:
      return NalUnitTypeEnum::CODED_SLICE_DPB;
    case 4:
      return NalUnitTypeEnum::CODED_SLICE_DPC;
    case 5:
      return NalUnitTypeEnum::CODED_SLICE_IDR;
    case 6:
      return NalUnitTypeEnum::SEI;
    case 7:
      return NalUnitTypeEnum::SPS;
    case 8:
      return NalUnitTypeEnum::PPS;
    case 9:
      return NalUnitTypeEnum::AUD;
    case 10:
      return NalUnitTypeEnum::END_OF_SEQUENCE;
    case 11:
      return NalUnitTypeEnum::END_OF_STREAM;
    case 12:
      return NalUnitTypeEnum::FILLER_DATA;
    case 13:
      return NalUnitTypeEnum::SPS_EXT;
    case 19:
      return NalUnitTypeEnum::CODED_SLICE_AUX;
  }
  if (nal_unit_type == 0 || (nal_unit_type >= 24 && nal_unit_type <= 31)) {
    return NalUnitTypeEnum::UNSPECIFIED;
  }
  if ((nal_unit_type >= 14 && nal_unit_type <= 18) || (nal_unit_type >= 20 && nal_unit_type <= 23)) {
    return NalUnitTypeEnum::RESERVED;
  }
  throw std::invalid_argument("Invalid nal_unit_type"+std::to_string(nal_unit_type));
}
