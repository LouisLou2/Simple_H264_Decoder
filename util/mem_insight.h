//
// Created by leo on 24-9-22.
//

#ifndef MEM_INSIGHT_H
#define MEM_INSIGHT_H
#include <cstdint>


class MemInsight {
public:
  static void printNextNBytes(uint8_t* data, uint16_t n);
};



#endif //MEM_INSIGHT_H
