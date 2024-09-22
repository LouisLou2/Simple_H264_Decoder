//
// Created by leo on 24-9-22.
//

#ifndef NALU_READER_H
#define NALU_READER_H
#include <optional>

#include "../entity/nalu.h"


class NaluReader {
protected:
  virtual bool open() = 0;
  virtual std::optional<std::unique_ptr<Nalu>> getNalu() = 0;
  virtual void close() = 0;
public:
  virtual ~NaluReader() = default;
};



#endif //NALU_READER_H
