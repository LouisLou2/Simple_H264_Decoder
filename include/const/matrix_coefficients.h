//
// Created by leo on 24-9-23.
//

#pragma once
#include <cstdint>

enum class MatrixCoefEnum {
  GBR = 0, // 0
  BT709 = 1,
  Unspecified = 2,
  Reserved = 3, // 3, 15-255
  USFCCT47 = 4,
  BT470BG = 5,
  SMPTE170M = 6,
  SMPTE240M = 7,
  YCgCo = 8,
  BT2020_NCL = 9,
  BT2020_CL = 10,
  SMPTE2085 = 11,
  Chroma_Derived_CL = 12,
  Chroma_Derived_NCL = 13,
  ICtCp = 14,
};

class MatrixCoefUtil {
public:
  inline static MatrixCoefEnum getMatrixCoefficients(uint8_t matrix_coefficients);
};


inline MatrixCoefEnum MatrixCoefUtil::getMatrixCoefficients(uint8_t matrix_coefficients) {
  return (matrix_coefficients <= 14 ) ? static_cast<MatrixCoefEnum>(matrix_coefficients) : MatrixCoefEnum::Reserved;
}

