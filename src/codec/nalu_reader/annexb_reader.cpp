//
// Created by leo on 24-9-17.
//
#include "codec/nalu_reader/annexb_reader.h"

#include <cassert>
#include <cstring>

#include "entity/nalu/nalu.h"
#include "util/buf_match.h"

#define READ_LEN (1024*20)
#define BUF_REMAIN_THRESHOLD 512

void AnnexbReader::readToBuffer() {
  uint32_t readlen = READ_LEN;
  // create a new buffer
  size_t bufLeft = bufLen - nowBufAt; // >=0
  auto* newBuf = new uint8_t[bufLeft + readlen];
  // read the new data
  infile.read(reinterpret_cast<char*>(newBuf + bufLeft), readlen);
  size_t readedLen = infile.gcount();
  if (readedLen < readlen) {
    toFileEnd = true;// indicate that the file reaches the end
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
  bufLen = bufLeft + readedLen;
  nowBufAt = 0;
}

/*
 * 返回一个pair，如果找到了start code，返回start code的位置和长度
 * 如果没有找到，返回nullptr和下一次寻找的起始位置，即start+returned_pair[1]的位置
 */
std::pair<const uint8_t*, uint32_t> AnnexbReader::findStartCode(const uint8_t* start, const uint8_t* end) const{
  auto begin = start;
  uint8_t nextStartCodeLen=0;
  while(true) {
    const uint8_t* nextStart = BufMatch::match00(begin,end);
    if (nextStart == end) {
      // 此时说明连两个连续的0都没有找到，说明在此buffer中没有start code，但是如果现在最后一个字节是0x00，这个0x00可能是start code的一部分
      if (*(nextStart-1)==0x00) {
        return {nullptr,end - start -1};
      }
      return {nullptr,end - start};
    }
    if (nextStart+2==end) {
      // 此时说明，两个0正好位于buffer的最后两个字节
      return {nullptr,end - start -2};
    }
    if (nextStart[2] == 1) {
      return {nextStart, 3};
    }
    if (nextStart[2] == 0) {
      if (nextStart + 3 == end) {
        return {nullptr,end - start -3};
      }
      if (nextStart[3] == 1) return {nextStart, 4};
      // 到这里说明出现000X的情况，则继续找
      begin = nextStart + 4;
      continue;
    }
    // 到这里说明出现了00X的情况，则继续找
    begin = nextStart + 3;
  }
}

uint8_t AnnexbReader::getStartCodeLen(const uint8_t* buffer) {
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
  return infile.is_open();
}

/*
 * 每次只解析一个nalu，解析完一个nalu, 把nowBufAt指向下一个nalu的开始码,
 * 可以保证一个nalu一定是从nowBufAt开始的
 */
std::optional<std::unique_ptr<Nalu>> AnnexbReader::getNalu() {
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
    if (!startCodeLen) return std::nullopt;
    // 开始寻找下一个start code
    // skip是从start开始的跳跃数
    size_t skip = searchNextStartFrom==0 ? startCodeLen : searchNextStartFrom;

    auto res = findStartCode(start + skip, buf + bufLen);

    if (!res.first) {
      // 如果没找到，并且已经toFileEnd, 说明已经到文件尾部
      if (toFileEnd) {
        // for (size_t i = nowBufAt; i < bufLen; ++i) {
        //   // 使用 %02X 打印两位的十六进制数，不足两位时前面补0
        //   printf("%02X ", buf[i]);
        // }
        size_t thisNaluLen = bufLen - nowBufAt;
        nowBufAt = bufLen;
        return Nalu::getNalu(startCodeLen, start + startCodeLen, thisNaluLen - startCodeLen);
      }
      // 说明未搜寻到，但是给出了res.second作为从start + skip开始的跳跃数
      searchNextStartFrom = skip + res.second; // 下次从这个位置开始搜索，即start + searchNextStartFrom
      nowStartCodeLen = startCodeLen;
      needMore = true;
      continue;
    }
    // now we get the next start code location and length
    // first get the  nalu
    auto nalu=Nalu::getNalu(startCodeLen, start + startCodeLen, res.first - start - startCodeLen);
    // restore nowStartCodeLen in case of next iteration
    nowStartCodeLen = res.second;
    // set nowBufAt to next start code
    nowBufAt = res.first - buf;
    // reset searchNextStartFrom
    searchNextStartFrom = 0;
    // set needMore to false: because now we cant make sure that we need more data, so let the next iteration decide
    needMore = false;
    // return the nalu
    return nalu;
  }
}

void AnnexbReader::close() {
  // close file
  infile.close();
  // clear buffer
  delete[] buf; // delete nullptr has no effect
  // buf = nullptr; // not necessary
}
