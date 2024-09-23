//
// Created by leo on 24-9-17.
//

#include "entity/nalu.h"
#include <string>

#include "entity/sps_nalu.h"
#include "codec/data_filter.h"
#include "util/buf_match.h"
// #include "../util/mem_insight.h"

std::unique_ptr<Nalu> Nalu::getNalu(uint8_t startCodeLen, uint8_t* data, size_t len) {
  uint8_t nal_unit_type = data[startCodeLen] & 0x1f;
  NalUnitTypeEnum nalUnitType = NalUnitTypeUtil::getNalUnitType(nal_unit_type);
  switch (nalUnitType) {
  case NalUnitTypeEnum::SPS:
     return std::make_unique<SPSNalu>(startCodeLen, data, len);
   default:
     return std::make_unique<Nalu>(startCodeLen, data, len);
  }
}


// 这里的data是NALU最最开始的位置，即start code的首字节
Nalu::Nalu(uint8_t startCodeLen, uint8_t* data, size_t len):
startCodeLen(startCodeLen),
headerByte(data[startCodeLen]),
ebspLen(len - startCodeLen - 1){
   auto rbspPair = DataFilter::EBSP_to_RBSP(data + startCodeLen + 1, ebspLen);
   rbsp = std::move(rbspPair.first);//还需要再次移动，因为pair的first是左值，这里算正式接管内存
   rbspLen = rbspPair.second;
   nalUnitType = NalUnitTypeUtil::getNalUnitType(nal_unit_type());
}

std::string Nalu::to_string() const {
  return "forbidden_zero_bit: " + std::to_string(forbidden_zero_bit()) +
         ", nal_ref_idc: " + std::to_string(nal_ref_idc()) +
         ", nal_unit_type: " + std::to_string(nal_unit_type());
}
