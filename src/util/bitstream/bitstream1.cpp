//
// Created by leo on 24-9-21.
//

#include "util/bitstream/bitstream1.h"

#include <cassert>

BitStream1::BitStream1(uint8_t* buf, uint32_t bufLen) :
buf(buf), bufLen(bufLen), byteNow(buf), bitOffset(0) {
}

uint8_t BitStream1::readBit1() {
  uint8_t ret = (*byteNow >> (7-bitOffset)) & 1;
  if(bitOffset + 1==8) {
    ++byteNow;
    bitOffset = 0;
  }else
    ++bitOffset;
  return ret;
}

uint32_t BitStream1::readBitN(uint8_t n) {
  assert(n <= 32);
  uint32_t res = 0;
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
      (32 - used - resBitFrom)
      | res;
    resBitFrom += used;
    n -= used;
    if(bitOffset + used == 8) {
      ++byteNow;
      bitOffset = 0;
    }else
      bitOffset += used;
  }
  return res;
}

void BitStream1::backward1() {
  if(bitOffset) {
    --bitOffset;
  }else {
    --byteNow;
    bitOffset = 7;
  }
}

void BitStream1::backwardN(uint8_t n) {
  byteNow -= (n / 8);
  uint8_t bitback = (n % 8);
  if (bitOffset < bitback) {
    --byteNow;
    bitOffset = 8 - (bitback - bitOffset);
  } else {
    bitOffset -= bitback;
  }
}

void BitStream1::reset(uint8_t* buf, uint32_t bufLen) {
  this->buf = buf;
  this->bufLen = bufLen;
  byteNow = buf;
  bitOffset = 0;
}

uint32_t BitStream1::readUE() {
  uint32_t leadingZeroBits = 0;
  while (readBit1() == 0) ++leadingZeroBits;
  // 最多解析32位,故0 seq 最长为32-1=31
  assert (leadingZeroBits < 32);
  return (1 << leadingZeroBits) - 1 + readBitN(leadingZeroBits);
}

int32_t BitStream1::readSE() {
  uint32_t ue = readUE();
  return (ue & 1) ? (ue + 1) >> 1 : -(ue>>1);
}
