//
// Created by leo on 24-9-23.
//

#ifndef H264_LEVEL_MAP_H
#define H264_LEVEL_MAP_H
#include <cassert>
#include <cstdint>
#include <map>
#include "entity/level_limits.h"

class H264LevelMap {
  static std::map<uint8_t, LevelLimits> levelMap;
public:
  inline static uint32_t getMaxDpbMbs(uint8_t level);
};

inline uint32_t H264LevelMap::getMaxDpbMbs(uint8_t level) {
  auto it = levelMap.find(level);
  assert(it != levelMap.end());
  return it->second.maxDpbMbs;
}

#endif //H264_LEVEL_MAP_H
