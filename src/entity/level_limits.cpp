//
// Created by leo on 24-9-23.
//

#include "entity/level_limits.h"

LevelLimits::LevelLimits(
  uint32_t maxMBPS, uint32_t maxFS, uint32_t maxDpbMbs, uint32_t maxBR, uint32_t maxCPB,
  uint32_t maxVmvR, uint32_t minCR, uint32_t maxMvsPer2Mb):
  maxMBPS(maxMBPS), maxFS(maxFS), maxDpbMbs(maxDpbMbs), maxBR(maxBR), maxCPB(maxCPB), maxVmvR(maxVmvR), minCR(minCR), maxMvsPer2Mb(maxMvsPer2Mb) {}