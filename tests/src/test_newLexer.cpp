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

TEST(Test_StateMachine, _1){
    StateMachine machine;
    std::string code = "a 123 ";

    std::vector<StateType> actual_res;
    for (char i : code){
        auto res = machine.accept(i);
        if (res != nullptr){
            actual_res.push_back(*res);
        }
    }

    std::vector<StateType> expected_res = {StateType::IDENT, StateType::INT_CONST};

    EXPECT_EQ(actual_res.size(), expected_res.size());
    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

TEST(Test_StateMachine, _2){
    StateMachine machine;
    std::string code = "a 123 while _a ";

    std::vector<StateType> actual_res;
    for (char i : code){
        auto res = machine.accept(i);
        if (res != nullptr){
            actual_res.push_back(*res);
        }
    }

    std::vector<StateType> expected_res = {StateType::IDENT, StateType::INT_CONST, StateType::KEYWORD, StateType::IDENT};

    ASSERT_EQ(actual_res.size(), expected_res.size());
    for (int i=0; i<actual_res.size(); i++){
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

