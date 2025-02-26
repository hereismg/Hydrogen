//
// Created by Magnesium on 2025/2/24.
//

#include <gtest/gtest.h>
#include <fstream>
#include "Token.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    hdg::Position position;
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

class PositionTest: public testing::TestWithParam<std::string>{};

TEST_P(PositionTest, First){

}