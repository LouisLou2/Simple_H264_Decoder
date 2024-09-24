//
// Created by leo on 24-9-24.
//

#ifndef TEST_NALU_H
#define TEST_NALU_H
#include <string>

#include "nalu/nalu.h"


class TestNalu : public Nalu{
public:
    TestNalu();
    [[nodiscard]] std::string to_string() const override;
    ~TestNalu() override;
};



#endif //TEST_NALU_H
