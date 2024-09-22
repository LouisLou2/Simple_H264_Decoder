//
// Created by leo on 24-9-17.
//

#include "nalu.h"
#include <cstring>
#include <string>

#include "sps_nalu.h"
#include "../util/buf_match.h"
#include "../util/mem_insight.h"

 std::pair<uint8_t*, uint32_t> Nalu::parseRBSP(const uint8_t* ebsp, uint32_t len) {
  auto* rbsp = new uint8_t[len]; // 几乎肯定不会超过ebspLen，但是先分配ebspLen
  uint32_t rbspLen = 0;
  const uint8_t* searchBegin = ebsp;
  const uint8_t* searchEnd = ebsp + len;
  uint32_t appendLen;
  while(true) {
    const uint8_t* ind003 = BufMatch::match003(searchBegin, searchEnd);
    if (ind003 == searchEnd || ind003 + 3 == searchEnd) {
      appendLen = searchEnd - searchBegin;
      // 没有找到003
      memcpy(rbsp + rbspLen, searchBegin, appendLen);
      rbspLen += appendLen;
      break;
    }
    // 找到了003且003不是ebsp的最后三个字节
    // 检查003后面的一个字节是否为0x00-0x03
    if (*(ind003 + 3) > 0x04) {
      // 不是00-03
      appendLen = ind003 - searchBegin + 4;
      memcpy(rbsp + rbspLen, searchBegin, appendLen);
      rbspLen += appendLen;
      searchBegin = ind003 + 4;
      continue;
    }
    // 003后面的一个字节是00-03
    MemInsight::printNextNBytes(ind003, 12);
    appendLen = ind003 - searchBegin + 2;
    memcpy(rbsp + rbspLen, searchBegin, appendLen);
    rbspLen += appendLen;
    rbsp[rbspLen++] = *(ind003 + 3);
    searchBegin = ind003 + 4;
  }
   return {rbsp, rbspLen};
}

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
   auto rbspPair = parseRBSP(data + startCodeLen + 1, ebspLen);
   rbps = rbspPair.first;
   rbspLen = rbspPair.second;
   nalUnitType = NalUnitTypeUtil::getNalUnitType(nal_unit_type());
}

std::string Nalu::to_string() const {
  return "forbidden_zero_bit: " + std::to_string(forbidden_zero_bit()) +
         ", nal_ref_idc: " + std::to_string(nal_ref_idc()) +
         ", nal_unit_type: " + std::to_string(nal_unit_type());
}
