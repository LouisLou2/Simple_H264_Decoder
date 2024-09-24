//
// Created by leo on 24-9-17.
//

#ifndef ANNEXB_READER_H
#define ANNEXB_READER_H
#include <cstdint>
#include <fstream>
#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "nalu_reader.h"
#include "entity/nalu/nalu.h"

class AnnexbReader :public NaluReader{
  // file source
  std::string_view filename;
  std::ifstream infile;
  bool toFileEnd;
  bool needMore;
  // buffer
  uint8_t* buf;
  size_t bufLen;
  size_t nowBufAt;
  // parsing
  /*
   * 次字段用于已经解析出了的start code的长度，但是由于buffer不足，未能找到下一个start code，
   * 这里把他保存下来，下次解析时，先判断这个字段，如果不为0，就直接使用这个字段，不再重新解析.
   * searchNextStartFrom同样，上一次在已有的buffer中都找不到下一个start code，但是可以下一次从这个位置开始搜索
   */
  uint8_t nowStartCodeLen;
  size_t searchNextStartFrom;
  // private func
  void readToBuffer();
  std::pair<const uint8_t*,uint32_t> findStartCode(const uint8_t* start, const uint8_t* end) const;
public:
  // constructor
  explicit AnnexbReader(std::string_view filename);
  static uint8_t getStartCodeLen(const uint8_t*buffer);
  bool open() override;
  std::optional<std::unique_ptr<Nalu>> getNalu() override;
  void close() override;
};



#endif //ANNEXB_READER_H
