//
// Created by leo on 24-9-17.
//

#include "nalu.h"

#include <cstring>
#include <string>

Nalu::Nalu(uint8_t startCodeLen, uint8_t* data, size_t len) :
  startCodeLen(startCodeLen),
  len(len),
  headerByte(data[startCodeLen]){
  // copy data
  this->data = new uint8_t[len];
  memcpy(this->data, data, len);
}

std::string Nalu::to_string() const {
  return "forbidden_zero_bit: " + std::to_string(forbidden_zero_bit()) +
         ", nal_ref_idc: " + std::to_string(nal_ref_idc()) +
         ", nal_unit_type: " + std::to_string(nal_unit_type());
}
