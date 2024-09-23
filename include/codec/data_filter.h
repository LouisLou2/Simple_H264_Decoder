//
// Created by leo on 24-9-23.
//

#ifndef BIT_FILTER_H
#define BIT_FILTER_H
#include <memory>

class DataFilter {
public:
  static std::pair<std::unique_ptr<uint8_t[]>, uint32_t> EBSP_to_RBSP(uint8_t* ebsp, size_t len);
};



#endif //BIT_FILTER_H
