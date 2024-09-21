//
// Created by leo on 24-9-21.
//

#ifndef BITSTREAM_H
#define BITSTREAM_H
#include <cstdint>

class BitStream {
protected:
  virtual uint8_t readBit1() = 0;
  virtual uint32_t readBitN(uint8_t n) = 0;
  virtual void resetBuffer(uint8_t* buf, uint32_t bufLen) = 0;
public:
  virtual ~BitStream() = default;
};



#endif //BITSTREAM_H
