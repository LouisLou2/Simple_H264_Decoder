//
// Created by leo on 24-9-24.
//

#include "entity/nalu/aud_nalu.h"

// 不需要parse RBSP, 我们知道只有一个字节
AUDNalu::AUDNalu(uint8_t startCodeLen,uint8_t* data, uint32_t len) : Nalu(startCodeLen, data, len,false) {
  data += naluHeader.nuhBytes;
  // read 3 bits, 注意是前三个bit
  primary_pic_type = (*data & 0b11100000) >> 5;
}

std::string AUDNalu::to_string() const {
  return "It's an AUD Nalu with primary_pic_type: " + std::to_string(primary_pic_type);
}
