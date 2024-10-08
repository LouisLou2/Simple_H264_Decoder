//
// Created by leo on 24-9-21.
//

#ifndef BITSTREAM1_H
#define BITSTREAM1_H
#include "bitstream.h"

class BitStream1 final : public BitStream{
  uint8_t* buf;
  uint32_t bufLen;
  uint8_t* byteNow;
  uint8_t bitOffset;
public:
  // get now bitstream state
  uint8_t getBitOffset() override{return bitOffset;}
  uint32_t getByteOffset() override{return byteNow - buf;}
  BitStream1(uint8_t* buf, uint32_t bufLen);
  // 从buf中读取一个比特
  uint8_t readBit1() override;
  // 从buf中直接读取n个比特作为无符号数
  uint32_t readBitN(uint8_t n) override;
  // 回退一个比特
  void backward1() override;
  // 回退n个比特
  void backwardN(uint8_t n) override;
  // 重置buf
  void reset(uint8_t* buf, uint32_t bufLen) override;
  // 无符号指数哥伦布编码
  uint32_t readUE() override;
  // 有符号指数哥伦布编码
  int32_t readSE() override;

  inline void skipThisByteLeft() override;
};

inline void BitStream1::skipThisByteLeft() {
  bitOffset = 0;
  ++byteNow;
}


#endif //BITSTREAM1_H
