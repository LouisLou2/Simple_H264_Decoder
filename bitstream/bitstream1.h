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
  BitStream1(uint8_t* buf, uint32_t bufLen);
  uint8_t readBit1() override;
  uint32_t readBitN(uint8_t n) override;
  void resetBuffer(uint8_t* buf, uint32_t bufLen) override;
};



#endif //BITSTREAM1_H
