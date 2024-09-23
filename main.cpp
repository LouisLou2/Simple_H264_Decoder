#include <cstdio>
#include <string_view>

#include "test/teat_read_nalu.h"
#include "test/test_bitstream.h"

int main() {
  std::unique_ptr<int> it = std::make_unique<int>(10);
  std::unique_ptr itt= std::move(it);
  std::string_view h264FilePath = "/home/leo/CLionProjects/h264decoder/resource/bejeweled_6s_annexb.h264";
  auto nalus=getReadedNalus(h264FilePath);
  return 0;
}
