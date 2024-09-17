//
// Created by leo on 24-9-17.
//
#include "annexb_reader.h"

#include <cassert>
#include <cstring>

#define READ_LEN (1024*2)
#define BUF_REMAIN_THRESHOLD 200

// for static
uint8_t AnnexbReader::startcode1[3] = {0x00,0x00,0x01};
uint8_t AnnexbReader::startcode2[4] = {0x00,0x00,0x00,0x01};
std::boyer_moore_searcher<uint8_t*> AnnexbReader::startCodeSearcher1(startcode1, startcode1+3);
std::boyer_moore_searcher<uint8_t*> AnnexbReader::startCodeSearcher2(startcode2, startcode2+4);

void AnnexbReader::readToBuffer() {
  uint32_t readlen = READ_LEN;
  // create a new buffer
  size_t bufLeft = bufLen - nowBufAt; // >=0
  auto* newBuf = new uint8_t[bufLeft + readlen];
  // read the new data
  infile.read(reinterpret_cast<char*>(newBuf + bufLeft), readlen);
  size_t readedLen = infile.gcount();
  if (readedLen < readlen) {
    toFileEnd = true;// indicate that the file is end
    if(readedLen == 0) {
      // no data readed
      delete [] newBuf;
      return;
    }
  }
  // copy the remaining data
  if (buf) {
    memcpy(newBuf, buf + nowBufAt, bufLeft);
    delete [] buf;
  }
  // update buffer
  buf = newBuf;
  bufLen = bufLeft + readlen;
  nowBufAt = 0;
}

uint8_t AnnexbReader::getStartCodeLen(uint8_t* buffer) {
  // 调用前保证buffer的长度至少为4
  if (buffer[0] == 0 && buffer[1] == 0) {
    if (buffer[2] == 1) {
      return 3;
    }
    if (buffer[2] == 0 && buffer[3] == 1) {
      return 4;
    }
  }
  return 0; // not found
}

AnnexbReader::AnnexbReader(std::string_view filename) :
  filename(filename),
  buf(nullptr),
  bufLen(0),
  nowBufAt(0),
  toFileEnd(false),
  needMore(false),
  nowStartCodeLen(0),
  searchNextStartFrom(0){
}

bool AnnexbReader::open() {
  infile.open(filename.data(), std::ios::binary);
  if (!infile.is_open()) {
    return false;
  }
  return true;
}

/*
 * 每次只解析一个nalu，解析完一个nalu, 把nowBufAt指向下一个nalu的开始码,
 * 可以保证一个nalu一定是从nowBufAt开始的
 */
std::optional<Nalu> AnnexbReader::getNalu() {
  while(true) {
    // 若没有到达文件尾部，且buffer中剩余数据不足BUF_REMAIN_THRESHOLD字节，则读取新数据
    if(!toFileEnd && (needMore || bufLen - nowBufAt < BUF_REMAIN_THRESHOLD)) {
      readToBuffer();
    }
    // 开始寻找这个nalu的开始码
    // 如果已经记录，就直接使用
    uint8_t* start = buf + nowBufAt;
    // 确保buffer中剩余数据长度至少为4
    // 这里只可能发生在已经解析完毕所有nalu,但是仍尝试读取时
    if (bufLen - nowBufAt < 4) {
      return std::nullopt;
    }
    // 获取start code的长度
    uint8_t startCodeLen = nowStartCodeLen==0 ? getStartCodeLen(start) : nowStartCodeLen;
    // 开始寻找下一个start code
    size_t skip = searchNextStartFrom==0 ? startCodeLen : searchNextStartFrom;
    uint8_t* nextStart = std::search(start + skip, buf + bufLen, startCodeSearcher1);
    uint8_t nextStartCodeLen;
    if (nextStart == buf + bufLen) {
      // 尝试第二个searcher
      nextStart = std::search(start + skip, buf + bufLen, startCodeSearcher2);
      if (nextStart == buf + bufLen){
        // 即在已有的buffer中未找到start code
        // 记录现在的start code长度
        nowStartCodeLen = startCodeLen;
        searchNextStartFrom = bufLen - nowBufAt;
        needMore = true;
        continue;
      }
      nextStartCodeLen = 4;
    }else {
      nextStartCodeLen = 3;
    }
    // now we get the next start code location and length
    // first get the  nalu
    Nalu nalu(startCodeLen, start, nextStart - start);
    // restore nowStartCodeLen in case of next iteration
    nowStartCodeLen = nextStartCodeLen;
    // set nowBufAt to next start code
    nowBufAt = nextStart - buf;
    // reset searchNextStartFrom
    searchNextStartFrom = 0;
    // set needMore to false: because now we dont think we undoubtedly need more data, so let the next iteration decide
    needMore = false;
    // return the nalu
    return nalu;
  }
}

void AnnexbReader::close() {
  // close file
  infile.close();
  // clear buffer
  if (buf) {
    delete[] buf;
    // buf = nullptr; // not necessary
  }
}
