//
// Created by leo on 24-9-17.
//

#ifndef NALU_H
#define NALU_H
#include <cstdint>
#include <cstddef>
#include <string_view>

class Nalu {
  uint8_t startCodeLen; // 3 or 4
  uint8_t headerByte; // headerByte except the start code part
  uint8_t* ebsp;
  uint32_t ebspLen;
  // uint8_t* rbsp; // 中间产物不要吧
  uint8_t* rbsp;
  uint32_t rbspLen;
public:
  // cons
  Nalu(uint8_t startCodeLen, uint8_t* data, size_t len);

  [[nodiscard]] uint32_t getEbspLen() const { return ebspLen; }
  [[nodiscard]] uint32_t getRbspLen() const { return rbspLen; }
  [[nodiscard]] uint8_t* getEbsp() const { return ebsp; }
  [[nodiscard]] uint8_t* getRbsp() const { return rbsp; }

  [[nodiscard]] bool forbidden_zero_bit() const;
  [[nodiscard]] uint8_t nal_ref_idc() const;
  [[nodiscard]] uint8_t nal_unit_type() const;

  void parse_RBSP_delete_EBSP();

  [[nodiscard]] std::string to_string() const;
  // [[nodiscard]] size_t length() const { return len; }
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

#endif //NALU_H
