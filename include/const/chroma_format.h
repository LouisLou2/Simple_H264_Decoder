//
// Created by leo on 24-9-23.
//

#ifndef CHROMA_FORMAT_H
#define CHROMA_FORMAT_H
#include <cassert>
#include <cstdint>

enum class ChromaFormat {
  MONOCHROME = 0,
  YUV420 = 1,
  YUV422 = 2,
  YUV444 = 3,
};

class ChromaFormatUtil {
public:
  inline static ChromaFormat getChromaFormat(uint8_t chroma_format_idc);
};

inline ChromaFormat ChromaFormatUtil::getChromaFormat(uint8_t chroma_format_idc) {
  assert(chroma_format_idc <= 3);
  return static_cast<ChromaFormat>(chroma_format_idc);
}


#endif //CHROMA_FORMAT_H
