//
// Created by leo on 24-9-23.
//
#pragma once
#include <cstdint>

enum class TransferCharacEnum {
  Reserved = 0,//0, 3, 19-255
  BT709 = 1,
  Unspecified = 2,
  ADG2_2 = 4,// assumed display gamma 2.2
  ADG2_8 = 5,// assumed display gamma 2.8
  SMPTE170M = 6,
  SMPTE240M = 7,
  Linear = 8,
  Log100 = 9,
  Log100Sqrt10 = 10,
  IEC61966_2_4 = 11,
  BT1361 = 12,
  IEC61966_2_1 = 13,
  BT2020_10 = 14,
  BT2020_12 = 15,
  SMPTE2084 = 16,
  SMPTE428 = 17,
  ARIB_STD_B67 = 18,
};

class TransferCharacUtil {
public:
  inline static TransferCharacEnum getTransferCharac(uint8_t transfer_charac);
};

inline TransferCharacEnum TransferCharacUtil::getTransferCharac(uint8_t transfer_charac) {
  return (transfer_charac <=18 && transfer_charac != 3) ? static_cast<TransferCharacEnum>(transfer_charac) : TransferCharacEnum::Reserved;
}