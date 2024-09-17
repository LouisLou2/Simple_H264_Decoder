//
// Created by leo on 24-9-17.
//

#include "nalu.h"

#include <cstring>

Nalu::Nalu(uint8_t startCodeLen, uint8_t* data, size_t len) :
  startCodeLen(startCodeLen),
  len(len) {
  // copy data
  this->data = new uint8_t[len];
  memcpy(this->data, data, len);
}
