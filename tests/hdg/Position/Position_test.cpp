//
// Created by Magnesium on 2025/2/24.
//

#include <gtest/gtest.h>
#include <fstream>
#include "Lexer.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    hdg::Position position;
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, SECOND){
    std::ifstream file("../tests/src/Position/code1.hdg");

    ASSERT_TRUE(file.is_open());

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string code = buffer.str();

    hdg::Lexer lexer;
    auto actual_res = lexer.run("<std>", &code);
    std::vector<hdg::Token> expected_res = {hdg::Token::IDENT};
    std::cout << expected_res << std::endl;


    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i].getType(), expected_res[i].getType());
    }
}

class PositionTest: public testing::TestWithParam<std::string>{};

TEST_P(PositionTest, First){

}