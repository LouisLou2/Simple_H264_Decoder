//
// Created by leo on 24-9-22.
//

#ifndef BUF_MATCH_H
#define BUF_MATCH_H
#include <cstdint>
#include <functional>

class BufMatch {
  static uint8_t pattern[3];
  static std::boyer_moore_searcher<uint8_t*> searcher00;
  static std::boyer_moore_searcher<uint8_t*> searcher003;
public:
  static uint8_t* match00(uint8_t* buf, uint8_t* end);
  static uint8_t* match003(uint8_t* buf, uint8_t* end);
};


inline uint8_t* BufMatch::match00(uint8_t* buf, uint8_t* end) {
  return std::search(buf, end, searcher00);
}

inline uint8_t* BufMatch::match003(uint8_t* buf, uint8_t* end) {
  return std::search(buf, end, searcher003);
}

#endif //BUF_MATCH_H
