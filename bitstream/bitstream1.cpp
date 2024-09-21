//
// Created by leo on 24-9-21.
//

#include "bitstream1.h"

#include <cassert>

BitStream1::BitStream1(uint8_t* buf, uint32_t bufLen) :
buf(buf), bufLen(bufLen), byteNow(buf), bitOffset(0) {
}

uint8_t BitStream1::readBit1() {
  uint8_t ret = (*byteNow >> (7-bitOffset)) & 1;
  ++bitOffset;
  if (bitOffset == 8) {
    ++byteNow;
    bitOffset = 0;
  }
  return ret;
}

uint32_t BitStream1::readBitN(uint8_t n) {
  assert(n <= 32);
  uint32_t res=0;
  uint8_t resBitFrom=32-n;
  uint8_t used;
  uint8_t mov;
  while(n) {
    used = n > (8 - bitOffset) ? (8 - bitOffset) : n;
    mov = 8 - (bitOffset + used);
    res =
      ( static_cast<uint32_t>(*byteNow) >> mov
        &
        0xffffffff >> (32 - used)
      )
      <<
      ( 32-used-resBitFrom )
      | res;
    resBitFrom += used;
    n -= used;
    bitOffset += used;
    if (bitOffset == 8) {
      ++byteNow;
      bitOffset = 0;
    }
  }
  return res;
}

void BitStream1::resetBuffer(uint8_t* buf, uint32_t bufLen) {
  this->buf = buf;
  this->bufLen = bufLen;
  byteNow = buf;
  bitOffset = 0;
}
