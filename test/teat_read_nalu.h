//
// Created by leo on 24-9-21.
//
# pragma once

#include <cstdio>
#include <list>
#include <string_view>
#include <chrono>

#include "../annexb_reader.h"

uint64_t getFileSize(const char* fileName);

std::list<Nalu> getReadedNalus(std::string_view fileName);