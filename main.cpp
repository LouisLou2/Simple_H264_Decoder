#include <cstdio>
#include <string_view>
#include "test/test_bitstream.h"


int main() {
  std::string_view h264FilePath = "/home/leo/CLionProjects/h264decoder/resource/bejeweled_6s_annexb.h264";
  testBitRead(h264FilePath);
  return 0;
}
