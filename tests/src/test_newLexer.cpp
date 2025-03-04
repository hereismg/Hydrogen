//
// Created by Magnesium on 2025/3/4.
//
#include<gtest/gtest.h>
#include<NewLexer.h>
using namespace std;
using namespace hdg_lexer;

TEST(Test_CharType, _1){
    auto status = CharType::DIGITAL;
    string show = showCharType(status);
    EXPECT_EQ(show, "DIGITAL");
}

TEST(Test_CharType, _2){
    auto status = CharType::DIGITAL | CharType::LOWERCASE;
    string show = showCharType(status);
    EXPECT_EQ(show, "DIGITAL | LOWERCASE");
}

TEST(Test_CharType, _3){
    auto status = CharType::OTHER;
    string show = showCharType(status);
    EXPECT_EQ(show, "OTHER");
}

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

class Test_StateMachine_P: public testing::TestWithParam<std::tuple<std::string, std::vector<StateType>>>{};
TEST_P(Test_StateMachine_P, _1){
    auto [code, expected_res] = GetParam();

    StateMachine machine;

    std::vector<StateType> actual_res;
    for (char i : code){
        auto res = machine.update(i);
        if (res != nullptr){
            actual_res.push_back(*res);
        }
    }

    ASSERT_EQ(actual_res.size(), expected_res.size());
    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

INSTANTIATE_TEST_SUITE_P(Test_StateMachine, Test_StateMachine_P, testing::Values(
    std::tuple<std::string, std::vector<StateType>>{
            "{}123 ",
            {StateType::BRACKET, StateType::BRACKET, StateType::INT_CONST}
    },
    std::tuple<std::string, std::vector<StateType>>{
            "a 123 while _a ",
            {StateType::IDENT, StateType::INT_CONST, StateType::KEYWORD, StateType::IDENT}
    },
    std::tuple<std::string, std::vector<StateType>>{
            "a 123 ",
            {StateType::IDENT, StateType::INT_CONST}
    }
));
