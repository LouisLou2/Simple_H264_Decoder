//
// Created by leo on 24-9-22.
//

#ifndef NAL_UNIT_TYPE_H
#define NAL_UNIT_TYPE_H
#include <cstdint>

enum class NalUnitTypeEnum {
  UNSPECIFIED = 0, // 0 and 24-31
  CODED_SLICE_NON_IDR = 1,
  CODED_SLICE_DPA = 2,
  CODED_SLICE_DPB = 3,
  CODED_SLICE_DPC = 4,
  CODED_SLICE_IDR = 5,
  SEI = 6,
  SPS = 7,
  PPS = 8,
  AUD = 9,
  END_OF_SEQUENCE = 10,
  END_OF_STREAM = 11,
  FILLER_DATA = 12,
  SPS_EXT = 13,
  RESERVED = 14, // 14-18 and 20-23
  CODED_SLICE_AUX = 19,
};

class NalUnitTypeUtil {
public:
  static NalUnitTypeEnum getNalUnitType(uint8_t nal_unit_type);
};

#endif //NAL_UNIT_TYPE_H
