//
// Created by leo on 24-9-21.
//

#include "test/test_bitstream.h"
#include "test/teat_read_nalu.h"
#include "bitstream/bitstream1.h"

// int testBitRead(std::string_view fileName) {
//   auto totalByte = getFileSize(fileName.data());
//   auto nalus = getReadedNalus(fileName);
//   // begin bitstream test
//   auto begin = std::chrono::high_resolution_clock::now();
//   BitStream1 bs1(nullptr, 0);
//   for (const auto &nalu : nalus) {
//     bs1.resetBuffer(nalu.getEbsp(), nalu.getEbspLen());
//     for (uint32_t i = 0; i < nalu.getEbspLen() * 8; ++i) {
//       bs1.readBit1();
//     }
//   }
//   auto end = std::chrono::high_resolution_clock::now();
//   auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
//   printf("BitStream1 read %lu bits one by one in %ld microsec\n", totalByte*8, duration.count());
//
//   // begin bitstream test
//   begin = std::chrono::high_resolution_clock::now();
//   uint8_t sizes[10]={2,5,7,13,17,19,23,29,31,32};
//   for (const auto &nalu : nalus) {
//     bs1.resetBuffer(nalu.getEbsp(), nalu.getEbspLen());
//     size_t bitsLeft = nalu.getEbspLen() * 8;
//     uint32_t i=0;
//     while(true){
//       auto size = sizes[i++ % 10];
//       if (bitsLeft < size) break;
//       bs1.readBitN(size);
//       bitsLeft -= size;
//     }
//     bs1.readBitN(bitsLeft);
//   }
//   end = std::chrono::high_resolution_clock::now();
//   duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
//   printf("BitStream1 read %lu bits in batches in %ld microsec\n", totalByte*8, duration.count());
//   return 0;
// }

void testReadN() {
  uint8_t buf[8]={0b10101010, 0b01010101, 0b10101010, 0b01010101, 0b10101010, 0b01010101, 0b10101010, 0b01010101};
  BitStream1 bs1(buf, 8);
  for(uint8_t i=0;i<0x03;++i) bs1.readBit1();
  uint32_t res = bs1.readBitN(31);
  printf("res: %d\n", res);
}

void testUESE() {
  uint8_t buf[8]={0b00001111, 0b11010101, 0b10101010, 0b01010101, 0b10101010, 0b01010101, 0b10101010, 0b01010101};
  BitStream1 bs1(buf, 8);
  auto res=bs1.readSE();
  printf("res: %d\n", res);
}