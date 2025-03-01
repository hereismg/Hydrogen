////
//// Created by Magnesium on 2025/2/17.
////
//

#include <gtest/gtest.h>
#include <fstream>
#include <Lexer.h>
using namespace hdg;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    Lexer lexer;

    std::string code = "a + b = a";
    auto actual_res = lexer.run("<std>", &code);
    std::vector<Token> expected_res = {Token::IDENTIFIER, Token::PLUS, Token::IDENTIFIER, Token::EQ, Token::IDENTIFIER, Token::EF};

    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i].getType(), expected_res[i].getType());
    }
}

TEST(MAINTEST, TestWhatIsThis){
    int actual_res_1 = whatIsThis('a');
    EXPECT_EQ(actual_res_1, LegalChar::HEX_DIGITAL | LegalChar::LOWERCASE);

    int actual_res_2 = whatIsThis('A');
    EXPECT_EQ(actual_res_2, LegalChar::HEX_DIGITAL | LegalChar::UPPERCASE);

    int actual_res_3 = whatIsThis('_');
    EXPECT_EQ(actual_res_3, LegalChar::UNDERLINE);
}
