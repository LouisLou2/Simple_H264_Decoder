//
// Created by leo on 24-9-17.
//

#include "entity/nalu/nalu.h"
#include <string>

#include "bitstream/bitstream1.h"
#include "entity/nalu/sps_nalu.h"
#include "codec/data_filter.h"
#include "entity/test_nalu.h"
#include "util/buf_match.h"
// #include "../util/mem_insight.h"

// static
std::array<uint8_t,13> Nalu::specialProfileIdcs = {
  100, 110, 122, 244, 44, 83, 86, 118, 128, 138, 139, 134, 135
}; // baware: 这些顺序是按照标准的顺序来的，他们的出现可能性依次递减， 所以不要将他们有序然后二分， 反而是顺序查找更快

Nalu::Nalu(uint8_t startCodeLen, uint8_t* data, size_t len):
startCodeLen(startCodeLen){
  auto bs1 = BitStream1(data, len);
  BitStream& bs = bs1;
  naluHeader = NaluHeader(bs);
  // 负责将data中的EBSP转换为RBSP
  auto rbspPair = DataFilter::EBSP_to_RBSP(
    data + naluHeader.nuhBytes,
    len - naluHeader.nuhBytes
  ); // data + naluHeader.nuhBytes是EBSP的首地址
  rbsp = std::move(rbspPair.first);//还需要再次移动，因为pair的first是左值，这里算正式接管内存
  rbspLen = rbspPair.second;
}


// the only way to get nalu if you dont know the type
// 这里的data是不包括start code的
std::unique_ptr<Nalu> Nalu::getNalu(uint8_t startCodeLen, uint8_t* data, size_t len) {
  uint8_t nal_unit_type = data[0] & 0x1f;
  NalUnitTypeEnum nalUnitType = NalUnitTypeUtil::getNalUnitType(nal_unit_type);
  switch (nalUnitType) {
  case NalUnitTypeEnum::SPS:
     return std::make_unique<SPSNalu>(startCodeLen, data, len);
   default:
     return std::make_unique<TestNalu>();
  }
}


// 这里的data是NALU最最开始的位置，即start code的首字节
// Nalu::Nalu(uint8_t startCodeLen, uint8_t* data, size_t len):
// startCodeLen(startCodeLen),
// headerByte(data[startCodeLen]),
// ebspLen(len - startCodeLen - 1){
//    auto rbspPair = DataFilter::EBSP_to_RBSP(data + startCodeLen + 1, ebspLen);
//    rbsp = std::move(rbspPair.first);//还需要再次移动，因为pair的first是左值，这里算正式接管内存
//    rbspLen = rbspPair.second;
//    nalUnitType = NalUnitTypeUtil::getNalUnitType(nal_unit_type());
// }
