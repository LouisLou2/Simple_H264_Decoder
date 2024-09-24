//
// Created by leo on 24-9-17.
//

#ifndef NALU_H
#define NALU_H
#include <cstdint>
#include <cstddef>
#include <memory>

#include "nalu_header.h"
#include "const/nal_unit_type.h"

enum class NalUnitTypeEnum;

class Nalu {
protected:
  uint8_t startCodeLen; // 3 or 4
  NaluHeader naluHeader;
  uint32_t ebspLen{}; // length of the EBSP
  uint32_t rbspLen{}; // length of the RBSP
  std::unique_ptr<uint8_t[]> rbsp; // RBSP, 只是暂时性的，因为一旦各种成分解析完毕，就会被删除
  // func
  void clearRBSPBuffer();
  // cons
  // 这里的data是不包括start code的
  Nalu(uint8_t startCodeLen, uint8_t* data, size_t len);
  Nalu() = default; // TODO: for the convenience of testing, it should be removed in the future
public:
  static std::array<uint8_t,13> specialProfileIdcs;
  // simple factory pattern
  // 这里的data是不包括start code的
  static std::unique_ptr<Nalu> getNalu(uint8_t startCodeLen, uint8_t* data, size_t len);
  [[nodiscard]] uint32_t getEbspLen() const { return ebspLen; }
  [[nodiscard]] uint32_t getRbspLen() const { return rbspLen; }
  [[nodiscard]] virtual std::string to_string() const = 0;
  virtual ~Nalu() {
    clearRBSPBuffer();
  }
};

inline void Nalu::clearRBSPBuffer() {
  if (!rbsp) return;
  rbsp.reset();
  rbspLen = 0;
}

// inline bool Nalu::forbidden_zero_bit() const {
//   return headerByte >> 7;
// }
//
// inline uint8_t Nalu::nal_ref_idc() const {
//   return (headerByte >> 5) & 0x03;
// }
//
// inline uint8_t Nalu::nal_unit_type() const {
//   return headerByte & 0x1f;
// }

#endif //NALU_H
