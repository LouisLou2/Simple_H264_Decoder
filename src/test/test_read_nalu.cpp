//
// Created by leo on 24-9-21.
//

#include "test/teat_read_nalu.h"
#include <chrono>


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

std::list<Nalu*> getReadedNalus(std::string_view fileName) {
  NaluReader&& reader = AnnexbReader (fileName);
  if (!reader.open()) {
    fprintf(stderr, "Failed to open file %s\n", fileName.data());
    throw std::runtime_error("Failed to open file");
  }
  std::list<Nalu*> nalus;
  // begin time
  auto begin = std::chrono::high_resolution_clock::now();
  for (auto nalu = reader.getNalu(); nalu.has_value(); nalu = reader.getNalu()) {
    nalus.push_back(nalu.value().release());
    // printf("%s\n", nalu.value().to_string().c_str());
  }
  // end time
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
  printf("Read %lu nalus in %ld microsec\n", nalus.size(), duration.count());
  reader.close();
  return nalus;
}

// void testRBSP(const char* fileName) {
//   auto nalus = getReadedNalus(fileName);
//   uint32_t i = 0;
//   Nalu *spsNalu = nullptr;
//   for (auto &nalu : nalus) {
//     if(nalu->nal_unit_type()==7) {
//       spsNalu = nalu;
//     }
//   }
//   if (spsNalu == nullptr) {
//     fprintf(stderr, "No sps found in file %s\n", fileName);
//     return;
//   }
//   spsNalu->parse_RBSP_delete_EBSP();
//   BitStream1 bs1(spsNalu->getRbsp(), spsNalu->getRbspLen());
//   auto profile_idc = bs1.readBitN(8);
//   auto constraint_set0_flag = bs1.readBit1();
//   auto constraint_set1_flag = bs1.readBit1();
//   auto constraint_set2_flag = bs1.readBit1();
//   auto constraint_set3_flag = bs1.readBit1();
//   auto constraint_set4_flag = bs1.readBit1();
//   auto constraint_set5_flag = bs1.readBit1();
//   auto reserved_zero_2bits = bs1.readBitN(2);
//   auto level_idc = bs1.readBitN(8);
//   auto seq_parameter_set_id = bs1.readUE();
//   printf("profile_idc: %d\n", profile_idc);
// }