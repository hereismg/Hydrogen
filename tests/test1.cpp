////
//// Created by Magnesium on 2025/2/17.
////
//

#include <gtest/gtest.h>
#include <Token.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
