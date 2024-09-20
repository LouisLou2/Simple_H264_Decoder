#include <cstdio>
#include <list>
#include <string_view>
#include <chrono>
#include "annexb_reader.h"

int main() {
  std::string_view h264FilePath = "/home/leo/CLionProjects/h264decoder/resource/bejeweled_6s_annexb.h264";
  AnnexbReader reader(h264FilePath);
  if (!reader.open()) {
    fprintf(stderr, "Failed to open file %s\n", h264FilePath.data());
    return 1;
  }
  std::list<Nalu> nalus;
  // begin time
  auto begin = std::chrono::high_resolution_clock::now();
  for (auto nalu = reader.getNalu(); nalu.has_value(); nalu = reader.getNalu()) {
    nalus.push_back(nalu.value());
    // printf("%s\n", nalu.value().to_string().c_str());
  }
  // end time
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
  printf("Read %lu nalus in %ld microsec\n", nalus.size(), duration.count());
  reader.close();
  return 0;
}
