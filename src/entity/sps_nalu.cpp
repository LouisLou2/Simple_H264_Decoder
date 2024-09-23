//
// Created by leo on 24-9-22.
//

#include "entity/sps_nalu.h"
#include "bitstream/bitstream1.h"

// static
std::array<uint8_t,16> SPSNalu::Flat_4X4_16{16};
std::array<uint8_t,16> SPSNalu::Flat_8X8_16{16};


void SPSNalu::scaling_list(
  BitStream& bs,
  uint8_t* scalingList,
  uint8_t sizeOfScalingList,
  bool& useDefaultScalingMatrixFlag) {
  uint8_t lastScale = 8;
  uint8_t nextScale = 8;
  for(uint8_t j=0;j<sizeOfScalingList;++j) {
    if(nextScale) {
      uint8_t delta_scale = bs.readSE();
      nextScale = (lastScale + delta_scale + 256) % 256;
      useDefaultScalingMatrixFlag = (j == 0 && nextScale == 0);
    }
    scalingList[j] = (nextScale == 0) ? lastScale : nextScale;
    lastScale = scalingList[j];
  }
}

// TODO: 2017标准中NALU的Header没那么简单了，需要从新书写Header的部分
SPSNalu::SPSNalu(uint8_t startCodeLen, uint8_t* data, uint32_t size) : Nalu(startCodeLen, data, size) {
  // 委托给父类构造函数之后
  // bit stream从start code和nalu header之后开始
  BitStream1 bs1 = BitStream1(data,size);
  BitStream& bs = bs1;
}
