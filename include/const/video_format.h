//
// Created by leo on 24-9-23.
//

#ifndef VIDEO_FORMAT_H
#define VIDEO_FORMAT_H
#include <cstdint>

enum class VideoFormatEnum {
  Component = 0,
  PAL = 1,
  NTSC = 2,
  SECAM = 3,
  MAC = 4,
  Unspecified = 5,
  Reserved = 6
};

class VideoFormatUtil {
public:
  inline static VideoFormatEnum getVideoFormat(uint8_t video_format);
  static VideoFormatEnum defaultFormat() { return VideoFormatEnum::Unspecified; }
};

inline VideoFormatEnum VideoFormatUtil::getVideoFormat(uint8_t video_format) {
  return video_format <= 6 ? static_cast<VideoFormatEnum>(video_format) : VideoFormatEnum::Reserved;
}

#endif //VIDEO_FORMAT_H
