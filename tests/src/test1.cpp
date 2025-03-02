////
//// Created by Magnesium on 2025/2/17.
////
//

#include <gtest/gtest.h>
#include <fstream>
#include <Lexer.h>
using namespace hdg;

// Demonstrate some basic assertions.
TEST(FirstSuit, BasicAssertions) {
    Lexer lexer;

    std::string code = "a + b = a";
    auto actual_res = lexer.run("<std>", &code);
    std::vector<Token> expected_res = {Token::IDENTIFIER, Token::PLUS, Token::IDENTIFIER, Token::EQ, Token::IDENTIFIER, Token::EF};

    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i].getType(), expected_res[i].getType());
    }
}

TEST(FirstSuit, TestWhatIsThis){
    int actual_res_1 = whatIsThis('a');
    EXPECT_EQ(actual_res_1, LegalChar::HEX_DIGITAL | LegalChar::LOWERCASE);

    int actual_res_2 = whatIsThis('A');
    EXPECT_EQ(actual_res_2, LegalChar::HEX_DIGITAL | LegalChar::UPPERCASE);

    int actual_res_3 = whatIsThis('_');
    EXPECT_EQ(actual_res_3, LegalChar::UNDERLINE);
}

TEST(FirstSuit, TESTStatusMachine){
    StatusMachine machine;
    std::string code = "a 123 ";

    std::vector<StatusType> actual_res;
    for (char i : code){
        auto res = machine.accept(i);
        if (std::get<0>(res) == 1){
            actual_res.push_back(std::get<1>(res));
        }
    }

    std::vector<StatusType> expected_res = {StatusType::IDENT, StatusType::INT_CONST};

    EXPECT_EQ(actual_res.size(), expected_res.size());
    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

TEST(FirstSuit, TESTStatusMachine2){
    StatusMachine machine;
    std::string code = "a 123 while _a ";

    std::vector<StatusType> actual_res;
    for (char i : code){
        auto res = machine.accept(i);
        if (std::get<0>(res) == 1){
            actual_res.push_back(std::get<1>(res));
        }
    }

    std::vector<StatusType> expected_res = {StatusType::IDENT, StatusType::INT_CONST, StatusType::KEYWORD, StatusType::IDENT};

    ASSERT_EQ(actual_res.size(), expected_res.size());
    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}
