//
// Created by leo on 24-9-23.
//

#include <cstring>

#include "codec/data_filter.h"
#include "util/buf_match.h"
#include "util/mem_insight.h"

std::pair<std::unique_ptr<uint8_t[]>, uint32_t> DataFilter::EBSP_to_RBSP(uint8_t* ebsp, size_t len) {
  auto rbspPtr = std::make_unique<uint8_t[]>(len);
  // 在以下解析过程中，应该不会出现exception
  uint8_t* rbsp = rbspPtr.get();
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
    // 检查003后面的一个字节是否为0x00-0x03, 这里注释掉了，因为只要遵循H.264的规范，*(ind003 + 3) > 0x04 是不可能的
    // if (*(ind003 + 3) > 0x04) {
    //   // 不是00-03
    //   appendLen = ind003 - searchBegin + 4;
    //   memcpy(rbsp + rbspLen, searchBegin, appendLen);
    //   rbspLen += appendLen;
    //   searchBegin = ind003 + 4;
    //   continue;
    // }
    // 003后面的一个字节是00-03
    // MemInsight::printNextNBytes(ind003, 12);
    appendLen = ind003 - searchBegin + 2;
    memcpy(rbsp + rbspLen, searchBegin, appendLen);
    rbspLen += appendLen;
    rbsp[rbspLen++] = *(ind003 + 3);
    searchBegin = ind003 + 4;
  }
  return {std::move(rbspPtr), rbspLen};
}
