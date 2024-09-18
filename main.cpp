#include <cstdio>
#include <list>
#include <string_view>

#include "annexb_reader.h"

int main() {
  std::string_view h264FilePath = "/home/leo/CLionProjects/h264decoder/resource/bejeweled_6s_annexb.h264";
  AnnexbReader reader(h264FilePath);
  if (!reader.open()) {
    fprintf(stderr, "Failed to open file %s\n", h264FilePath.data());
    return 1;
  }
  std::list<Nalu> nalus;
  for (auto nalu = reader.getNalu(); nalu.has_value(); nalu = reader.getNalu()) {
    nalus.push_back(nalu.value());
  }
  reader.close();
  return 0;
}
