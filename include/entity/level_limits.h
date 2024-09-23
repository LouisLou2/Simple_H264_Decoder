//
// Created by leo on 24-9-23.
//

#ifndef LEVEL_LIMITS_H
#define LEVEL_LIMITS_H
#include <cstdint>

struct LevelLimits {
  const uint32_t maxMBPS;
  const uint32_t maxFS;
  const uint32_t maxDpbMbs;
  const uint32_t maxBR;
  const uint32_t maxCPB;
  const uint32_t maxVmvR;
  const uint32_t minCR;
  const uint32_t maxMvsPer2Mb;

  LevelLimits(uint32_t maxMBPS, uint32_t maxFS, uint32_t maxDpbMbs, uint32_t maxBR, uint32_t maxCPB, uint32_t maxVmvR, uint32_t minCR, uint32_t maxMvsPer2Mb);
};



#endif //LEVEL_LIMITS_H
