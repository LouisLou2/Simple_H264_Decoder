//
// Created by leo on 24-9-21.
//

#include "teat_read_nalu.h"


uint64_t getFileSize(const char* fileName) {
  // 打开文件
  std::ifstream file(fileName, std::ios::binary | std::ios::ate);  // 以二进制模式打开并移动到文件末尾
  // 检查文件是否成功打开
  if (file.is_open()) {
    // 获取文件大小
    std::streamsize fileSize = file.tellg();  // tellg() 返回当前文件指针的位置，即文件大小
    // 关闭文件
    file.close();
    return fileSize;
  }
  fprintf(stderr, "Failed to open file %s\n", fileName);
  return -1;
}

std::list<Nalu> getReadedNalus(std::string_view fileName) {
  AnnexbReader reader(fileName);
  if (!reader.open()) {
    fprintf(stderr, "Failed to open file %s\n", fileName.data());
    throw std::runtime_error("Failed to open file");
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
  return nalus;
}

void testRBSP(const char* fileName) {
  auto nalus = getReadedNalus(fileName);
  for (auto &nalu : nalus) {
    nalu.parse_RBSP_delete_EBSP();
  }
}