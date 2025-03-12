//
// Created by Magnesium on 2025/3/4.
//
#include<gtest/gtest.h>
#include<NewLexer.h>
#include<sml.hpp>
using namespace std;
using namespace hdg_lexer;

/**
 * 测试 showCharType 函数的行为是否符合预期
 * */
class Test_showCharType_P: public testing::TestWithParam<std::tuple<CharType, std::string>>{};
TEST_P(Test_showCharType_P, _){
    auto [inputCharType, expected] = GetParam();
    string actual = showCharType(inputCharType);
    EXPECT_EQ(actual, expected);
}
INSTANTIATE_TEST_SUITE_P(Test_showCharType, Test_showCharType_P, testing::Values(
        std::tuple<CharType, std::string>{
                CharType::DIGITAL,
                "DIGITAL"
        },
        std::tuple<CharType, std::string>{
                CharType::DIGITAL | CharType::LOWERCASE,
                "DIGITAL | LOWERCASE"
        },
        std::tuple<CharType, std::string>{
                CharType::OTHER,
                "OTHER"
        },
        std::tuple<CharType, std::string>{
                CharType::BRACKET_C | CharType::OPERATOR_C,
                "BRACKET_C | OPERATOR_C"
        }
));

TEST(Test_CharType, _4){
    std::string str = "0xA";
    std::vector<CharType> expected = {
            CharType::DIGITAL | CharType::HEX_DIGITAL,
            CharType::LOWERCASE,
            CharType::HEX_DIGITAL | CharType::UPPERCASE,
    };
    ASSERT_EQ(str.size(), expected.size());
    for (int i=0; i<str.size(); i++){
        auto actual = getCharType(str[i]);
        EXPECT_EQ(actual, expected[i]);
    }
}

TEST(Test_CharType, _5){
    std::string str = "海琛";
    std::vector<CharType> expected = {
            CharType::OTHER,
            CharType::OTHER,
            CharType::OTHER,
            CharType::OTHER,
            CharType::OTHER,
            CharType::OTHER,
    };
    ASSERT_EQ(str.size(), expected.size());
    for (int i=0; i<str.size(); i++){
        auto actual = getCharType(str[i]);
        EXPECT_EQ(actual, expected[i]);
    }
}

TEST(Test_CharType, _6){
    std::string str = "A Z _";
    std::vector<CharType> expected = {
            CharType::UPPERCASE | CharType::HEX_DIGITAL,
            CharType::BLANK,
            CharType::UPPERCASE,
            CharType::BLANK,
            CharType::UNDERLINE,
    };
    ASSERT_EQ(str.size(), expected.size());
    for (int i=0; i<str.size(); i++){
        auto actual = getCharType(str[i]);
        EXPECT_EQ(actual, expected[i]);
    }
}

TEST(Test_CharType, _7){
    std::string str = "{+";
    std::vector<CharType> expected = {
            CharType::BRACKET_C,
            CharType::OPERATOR_C,
    };
    ASSERT_EQ(str.size(), expected.size());
    for (int i=0; i<str.size(); i++){
        auto actual = getCharType(str[i]);
        EXPECT_EQ(actual, expected[i]);
    }
}

class Test_StateMachine_P: public testing::TestWithParam<std::tuple<std::string, std::vector<Token>>>{};
TEST_P(Test_StateMachine_P, _1){
    auto [code, expected_res] = GetParam();

    auto machine = StateMachine::buildStateMachine();

    std::vector<Token> actual_res;
    for (char i : code){
        auto res = machine->update(i);
        if (!res.empty()){
            actual_res.insert(actual_res.end(), res.begin(), res.end());
        }
    }

    ASSERT_EQ(actual_res.size(), expected_res.size());
    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i].getType(), expected_res[i].getType());
        EXPECT_EQ(actual_res[i].getVal(), expected_res[i].getVal());
    }
}

INSTANTIATE_TEST_SUITE_P(Test_StateMachine, Test_StateMachine_P, testing::Values(
    std::tuple<std::string, std::vector<Token>>{
            "{}123 ",
            {
                {StateType::BRACKET_S, "{"},
                {StateType::BRACKET_S, "}"},
                {StateType::INT_CONST, "123"}
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "a 123 while _a ",
            {
                {StateType::IDENT, "a"},
                {StateType::INT_CONST,"123" },
                {StateType::KEYWORD, "while"},
                {StateType::IDENT, "_a"}
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "a 123 ",
            {
                    {StateType::IDENT, "a"},
                    {StateType::INT_CONST,"123" }
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "for{} ",
            {
                    {StateType::KEYWORD, "for"},
                    {StateType::BRACKET_S,"{" },
                    {StateType::BRACKET_S,"}" }
            }
    }
//    std::tuple<std::string, std::vector<Token>>{
//            "1+(2*3)",
//            {StateType::KEYWORD, StateType::BRACKET_S, StateType::BRACKET_S}
//    }
));

TEST(TestToken, _1){
    auto tkn = Token(StateType::INT_CONST, "res");
}
