#include <cstdio>
#include <string_view>

#include "test/teat_read_nalu.h"
#include "test/test_bitstream.h"


int main() {
  std::string_view h264FilePath = "/home/leo/CLionProjects/h264decoder/resource/bejeweled_6s_annexb.h264";
  testRBSP(h264FilePath.data());
  return 0;
}
