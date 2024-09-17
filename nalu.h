//
// Created by leo on 24-9-17.
//

#ifndef NALU_H
#define NALU_H
#include <cstdint>

class Nalu {
  uint8_t startCodeLen;
  uint8_t* data;
  size_t len;
public:
  // cons
  Nalu(uint8_t startCodeLen, uint8_t* data, size_t len);
};



#endif //NALU_H
