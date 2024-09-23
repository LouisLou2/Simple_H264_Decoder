//
// Created by leo on 24-9-23.
//

#include "const/color_primary.h"

ColorPrimaryEnum ColorPrimaryUtil::getColorPrimary(uint8_t color_primary) {
  return (color_primary == 0 || color_primary == 3 || 13<=color_primary && color_primary<=21 || 23 <= color_primary)
  ? ColorPrimaryEnum::Reserved : static_cast<ColorPrimaryEnum>(color_primary);
}
