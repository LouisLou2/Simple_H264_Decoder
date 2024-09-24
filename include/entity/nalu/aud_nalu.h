//
// Created by leo on 24-9-24.
//

#ifndef AUD_NALU_H
#define AUD_NALU_H
#include "nalu.h"

class AUDNalu : public Nalu{
private:
  uint8_t primary_pic_type{};
public:
  AUDNalu() = default;
  // data 不包括start code
  AUDNalu(uint8_t startCodeLen, uint8_t* data, uint32_t len);

  [[nodiscard]] std::string to_string() const override;
};

#endif //AUD_NALU_H
