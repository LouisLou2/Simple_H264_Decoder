//
// Created by leo on 24-9-21.
//

#ifndef BITSTREAM_H
#define BITSTREAM_H
#include <cstdint>

class BitStream {
public:
  virtual uint8_t readBit1() = 0;
  // 1<= n <= 32
  virtual uint32_t readBitN(uint8_t n) = 0;
  virtual void backward1() = 0;
  // 0<= n<= 127
  virtual void backwardN(uint8_t n) = 0;

  virtual uint32_t readUE() = 0;
  virtual int32_t readSE() = 0;
  virtual void reset(uint8_t* buf, uint32_t bufLen) = 0;
public:
  virtual ~BitStream() = default;
};



#endif //BITSTREAM_H
