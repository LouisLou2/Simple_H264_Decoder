//
// Created by leo on 24-9-22.
//

#include "mem_insight.h"

#include <cstdio>

void MemInsight::printNextNBytes(uint8_t* data, uint16_t n) {
  if (data == nullptr) {
    printf("Error: Null pointer passed to function.\n");
    return;
  }
  printf("Next %d bytes: ",n);
  for (int i = 0; i < n; ++i) {
    printf("0x%02X ", data[i]); // %02X 用于打印两位十六进制数
  }
  printf("\n");
}
