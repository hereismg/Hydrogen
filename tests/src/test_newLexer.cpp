//
// Created by Magnesium on 2025/3/4.
//
#include<gtest/gtest.h>
#include<NewLexer.h>
#include<sml.hpp>
#include<memory>
using namespace std;
using namespace hdg_lexer;


TEST(TestSuit, _1){
    using namespace sml;


    Sender s{};
    auto ctx = std::make_shared<Context>("k k{} while ");

    sm<LexerSM> sm{s};
    ASSERT_EQ(sm.is(INIT), true);

    while (ctx.get()->getPtr() < ctx.get()->size()){
        char c1 = ctx.get()->getChar();
        sendEvent(c1, sm, ctx);
    }

    int a = 1;
}

TEST(Test_State, _1){
    using namespace sml;

    Sender s{};
    sm<LexerSM> sm{s};

    auto ctx = std::make_shared<Context>("20*33) ");

    char c1 = ctx.get()->getChar();
    sendEvent(c1, sm, ctx);
    ASSERT_TRUE(sm.is(INT_CONST));

    char c2 = ctx.get()->getChar();
    sendEvent(c2, sm, ctx);
    ASSERT_TRUE(sm.is(INT_CONST));
    
    char c3 = ctx.get()->getChar();
    sendEvent(c3, sm, ctx);
    ASSERT_TRUE(sm.is(INIT));
}

class Test_StateMachine_P: public testing::TestWithParam<std::tuple<std::string, std::vector<Token>>>{};
TEST_P(Test_StateMachine_P, _1){
    using namespace sml;

    auto [code, expected] = GetParam();

    Sender s{};
    auto ctx = std::make_shared<Context>(code);

    sm<LexerSM> sm{s};
    ASSERT_EQ(sm.is(INIT), true);

    while (ctx.get()->getPtr() < ctx.get()->size()){
        char c1 = ctx.get()->getChar();
        bool res = sendEvent(c1, sm, ctx);

        // 某个状态的事件无法处理！
        ASSERT_TRUE(res);
    }

    auto actual = ctx.get()->getTokenArr();

    for (int i=0; i<actual.size(); i++){
        EXPECT_EQ(actual[i].getType(), expected[i].getType());
        EXPECT_EQ(actual[i].getVal(),  expected[i].getVal());
    }
}

using namespace hdg;
INSTANTIATE_TEST_SUITE_P(TestSuit, Test_StateMachine_P, testing::Values(
    std::tuple<std::string, std::vector<Token>>{
            "{}123 ",
            {
                {TokenType::BRACKET_T , "{"},
                {TokenType::BRACKET_T , "}"},
                {TokenType::INT_CONST , "123"}
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "a 123 while _a ",
            {
                {TokenType::IDENT     , "a"},
                {TokenType::INT_CONST , "123"},
                {TokenType::KEYWORD   , "while"},
                {TokenType::IDENT     , "_a"}
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "a123 ",
            {
                {TokenType::IDENT, "a123"}
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "for{} ",
            {
                {TokenType::KEYWORD, "for"},
                {TokenType::BRACKET_T,"{" },
                {TokenType::BRACKET_T,"}" }
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "1234+(20*33) ",
            {
                {TokenType::INT_CONST,  "1234"},
                {TokenType::OPERATOR,   "+"},
                {TokenType::BRACKET_T,  "("},
                {TokenType::INT_CONST,  "20"},
                {TokenType::OPERATOR,   "*"},
                {TokenType::INT_CONST,  "33" },
                {TokenType::BRACKET_T,  ")" }
            }
    },
    std::tuple<std::string, std::vector<Token>>{
            "function     add\t( ) ",
            {
                {TokenType::KEYWORD,  "function"},
                {TokenType::IDENT,    "add"},
                {TokenType::BRACKET_T,"("},
                {TokenType::BRACKET_T,")"}
            }
    },
    std::tuple<std::string, std::vector<Token>>{
        "12.2 123",
        {
            {TokenType::FLOAT_CONST,  "12.2"},
            {TokenType::FLOAT_CONST,  "123"},
        }
}
));