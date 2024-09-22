//
// Created by leo on 24-9-22.
//

#include "sps_nalu.h"

SPSNalu::SPSNalu(uint8_t startCodeLen, uint8_t* data, uint32_t size) : Nalu(startCodeLen, data, size) {
  spsSpec = 0;
}
