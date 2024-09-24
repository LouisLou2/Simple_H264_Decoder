//
// Created by leo on 24-9-24.
//

#include "../../include/entity/test_nalu.h"

TestNalu::TestNalu():Nalu() {}

std::string TestNalu::to_string() const {
  return "TestNalu";
}

TestNalu::~TestNalu() = default;
