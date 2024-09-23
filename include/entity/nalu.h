//
// Created by leo on 24-9-17.
//

#ifndef NALU_H
#define NALU_H
#include <cstdint>
#include <cstddef>
#include <memory>

#include "../const/nal_unit_type.h"

enum class NalUnitTypeEnum;

class Nalu {
  NalUnitTypeEnum nalUnitType; // 5 bits, indicating the type of the NAL unit
  uint32_t ebspLen; // length of the EBSP
  uint32_t rbspLen; // length of the RBSP
  uint8_t startCodeLen; // 3 or 4
  uint8_t headerByte; // headerByte except the start code part
  std::unique_ptr<uint8_t[]> rbsp; // RBSP, 只是暂时性的，因为一旦各种成分解析完毕，就会被删除

  // func
  void clearRBSP();

public:
  // simple factory pattern
  static std::unique_ptr<Nalu> getNalu(uint8_t startCodeLen, uint8_t* data, size_t len);
  // cons
  Nalu(uint8_t startCodeLen, uint8_t* data, size_t len);

  [[nodiscard]] uint32_t getEbspLen() const { return ebspLen; }
  [[nodiscard]] uint32_t getRbspLen() const { return rbspLen; }
  [[nodiscard]] NalUnitTypeEnum getNalUnitType() const { return nalUnitType; }
  [[nodiscard]] bool forbidden_zero_bit() const;
  [[nodiscard]] uint8_t nal_ref_idc() const;
  [[nodiscard]] uint8_t nal_unit_type() const;

  [[nodiscard]] std::string to_string() const;
};

inline bool Nalu::forbidden_zero_bit() const {
  return headerByte >> 7;
}

inline uint8_t Nalu::nal_ref_idc() const {
  return (headerByte >> 5) & 0x03;
}

inline uint8_t Nalu::nal_unit_type() const {
  return headerByte & 0x1f;
}

inline void Nalu::clearRBSP() {
  rbsp.reset();
  rbspLen = 0;
}

#endif //NALU_H
