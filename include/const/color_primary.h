//
// Created by leo on 24-9-23.
//

#ifndef COLOR_PRIMARY_H
#define COLOR_PRIMARY_H
#include <cstdint>

enum class ColorPrimaryEnum {
  Reserved = 0, // 0,3,13-21, 23-255
  BT709 = 1,
  Unspecified = 2,
  BT470M = 4,
  BT470BG = 5,
  SMPTE170M = 6,
  SMPTE240M = 7,
  GenericFilm = 8,
  BT2020 = 9,
  SMPTE428 = 10,
  SMPTE431 = 11,
  SMPTE432 = 12,
  EBU3213 = 22,
};

class ColorPrimaryUtil {
public:
  static ColorPrimaryEnum getColorPrimary(uint8_t color_primary);
};

#endif //COLOR_PRIMARY_H
