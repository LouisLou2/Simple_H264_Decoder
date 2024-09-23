//
// Created by leo on 24-9-23.
//

#ifndef SAMPLE_ASPECT_RADIO_H
#define SAMPLE_ASPECT_RADIO_H
#include <cstdint>

enum class SampleAspectRadio {
  Unspecified = 0,
  SAR_Square = 1,
  SAR_12_11 = 2,
  SAR_10_11 = 3,
  SAR_16_11 = 4,
  SAR_40_33 = 5,
  SAR_24_11 = 6,
  SAR_20_11 = 7,
  SAR_32_11 = 8,
  SAR_80_33 = 9,
  SAR_18_11 = 10,
  SAR_15_11 = 11,
  SAR_64_33 = 12,
  SAR_160_99 = 13,
  SAR_4_3 = 14,
  SAR_3_2 = 15,
  SAR_2_1 = 16,
  Reserved = 17,
  Extended_SAR = 255
};

class SampleAspectRadioUtil {
public:
  inline static SampleAspectRadio getSampleAspectRadio(uint8_t aspect_ratio_idc);
};

inline SampleAspectRadio SampleAspectRadioUtil::getSampleAspectRadio(uint8_t aspect_ratio_idc) {
  if (aspect_ratio_idc<=16 || aspect_ratio_idc == 255)
    return static_cast<SampleAspectRadio>(aspect_ratio_idc);
  return SampleAspectRadio::Reserved;
}

#endif //SAMPLE_ASPECT_RADIO_H
