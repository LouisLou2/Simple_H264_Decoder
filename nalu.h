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
  size_t len; // the nalu length including the start code
  uint8_t headerByte; // headerByte except the start code part
  uint8_t* data; // whole data buf
public:
  // cons
  Nalu(uint8_t startCodeLen, uint8_t* data, size_t len);
  [[nodiscard]] bool forbidden_zero_bit() const;
  [[nodiscard]] uint8_t nal_ref_idc() const;
  [[nodiscard]] uint8_t nal_unit_type() const;
  [[nodiscard]] std::string to_string() const;

  [[nodiscard]] size_t length() const { return len; }
  [[nodiscard]] uint8_t* getData() const { return data; }
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
