//
// Created by leo on 24-9-17.
//

#include "nalu.h"
#include <cstring>
#include <string>
#include "util/buf_match.h"
#include "util/mem_insight.h"

Nalu::Nalu(uint8_t startCodeLen, uint8_t* data, size_t len) :
  startCodeLen(startCodeLen),
  headerByte(data[startCodeLen]),
  ebspLen(len - startCodeLen - 1),
  rbsp(nullptr),
  rbspLen(0){
  // copy data
  this->ebsp = new uint8_t[len - startCodeLen-1];
  memcpy(this->ebsp, data + startCodeLen + 1, len - startCodeLen - 1);
}

void Nalu::parse_RBSP_delete_EBSP() {
  rbsp = new uint8_t[ebspLen]; // 几乎肯定不会超过ebspLen，但是先分配ebspLen
  uint8_t* searchBegin = ebsp;
  uint8_t* searchEnd = ebsp + ebspLen;
  uint32_t appendLen;
  while(true) {
    uint8_t* ind003 = BufMatch::match003(searchBegin, searchEnd);
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
  delete [] ebsp;
  ebsp = nullptr;
  ebspLen = 0;
  // 将rbsp的长度更新为实际长度
  if(rbspLen == ebspLen) return;
  uint8_t* newRbsp = new uint8_t[rbspLen];
  memcpy(newRbsp, rbsp, rbspLen);
  delete [] rbsp;
  rbsp = newRbsp;
}

std::string Nalu::to_string() const {
  return "forbidden_zero_bit: " + std::to_string(forbidden_zero_bit()) +
         ", nal_ref_idc: " + std::to_string(nal_ref_idc()) +
         ", nal_unit_type: " + std::to_string(nal_unit_type());
}
