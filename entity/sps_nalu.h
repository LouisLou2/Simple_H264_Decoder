//
// Created by leo on 24-9-22.
//

#ifndef SPS_NALU_H
#define SPS_NALU_H
#include "nalu.h"

class SPSNalu : public Nalu {
  uint8_t spsSpec;
public:
  SPSNalu(uint8_t startCodeLen, uint8_t* data, uint32_t size);
};



#endif //SPS_NALU_H
