// #include<gtest/gtest.h>
// #include<NewLexer.h>
// #include<sml.hpp>
// #include<memory>
// using namespace std;
// using namespace hdg_lexer;


// TEST(TestSuit, _1){
//     using namespace sml;


//     Sender s{};
//     auto ctx = std::make_shared<Context>("k k{} while ");

//     sm<LexerSM> sm{s};
//     ASSERT_EQ(sm.is(INIT), true);

//     while (ctx.get()->getPtr() < ctx.get()->size()){
//         char c1 = ctx.get()->getChar();
//         sendEvent(c1, sm, ctx);
//     }

//     int a = 1;
// }

// TEST(Test_State, _1){
//     using namespace sml;

//     Sender s{};
//     sm<LexerSM> sm{s};

//     auto ctx = std::make_shared<Context>("20*33) ");

//     char c1 = ctx.get()->getChar();
//     sendEvent(c1, sm, ctx);
//     ASSERT_TRUE(sm.is(INT_CONST));

//     char c2 = ctx.get()->getChar();
//     sendEvent(c2, sm, ctx);
//     ASSERT_TRUE(sm.is(INT_CONST));
    
//     char c3 = ctx.get()->getChar();
//     sendEvent(c3, sm, ctx);
//     ASSERT_TRUE(sm.is(INIT));
// }

// class Test_StateMachine_P: public testing::TestWithParam<std::tuple<std::string, std::vector<Token>>>{};
// TEST_P(Test_StateMachine_P, _1){
//     using namespace sml;

//     auto [code, expected] = GetParam();

//     Lexer lexer;
//     auto actual = lexer.run(code);

//     // 注意，这的判断不包含 pos 变量
//     for (int i=0; i<actual.size(); i++){
//         EXPECT_EQ(actual[i].getType(), expected[i].getType());
//         EXPECT_EQ(actual[i].getVal(),  expected[i].getVal());
//     }
// }

// INSTANTIATE_TEST_SUITE_P(TestSuit, Test_StateMachine_P, testing::Values(
//     std::tuple<std::string, std::vector<Token>>{
//         "{}123 ",
//         {
//             {TokenType::BRACKET_T , "{"},
//             {TokenType::BRACKET_T , "}"},
//             {TokenType::INT_CONST , "123"}
//         }
//     },
//     std::tuple<std::string, std::vector<Token>>{
//         "a 123 while _a ",
//         {
//             {TokenType::IDENT     , "a"},
//             {TokenType::INT_CONST , "123"},
//             {TokenType::KEYWORD   , "while"},
//             {TokenType::IDENT     , "_a"}
//         }
//     },
//     std::tuple<std::string, std::vector<Token>>{
//         "a123 + 1 ",
//         {
//             {TokenType::IDENT    , "a123"},
//             {TokenType::OPERATOR , "+"},
//             {TokenType::INT_CONST, "1"}
//         }
//     },
//     std::tuple<std::string, std::vector<Token>>{
//         "for{} ",
//         {
//             {TokenType::KEYWORD, "for"},
//             {TokenType::BRACKET_T,"{" },
//             {TokenType::BRACKET_T,"}" }
//         }
//     },
//     std::tuple<std::string, std::vector<Token>>{
//         "1234+(20*33) ",
//         {
//             {TokenType::INT_CONST,  "1234"},
//             {TokenType::OPERATOR,   "+"},
//             {TokenType::BRACKET_T,  "("},
//             {TokenType::INT_CONST,  "20"},
//             {TokenType::OPERATOR,   "*"},
//             {TokenType::INT_CONST,  "33" },
//             {TokenType::BRACKET_T,  ")" }
//         }
//     },
//     std::tuple<std::string, std::vector<Token>>{
//         "function     add\t( ) ",
//         {
//             {TokenType::KEYWORD,  "function"},
//             {TokenType::IDENT,    "add"},
//             {TokenType::BRACKET_T,"("},
//             {TokenType::BRACKET_T,")"}
//         }
//     },
//     std::tuple<std::string, std::vector<Token>>{
//         "12.2 123 ",
//         {
//             {TokenType::FLOAT_CONST, "12.2"},
//             {TokenType::INT_CONST,   "123"},
//         }
//     },
//     std::tuple<std::string, std::vector<Token>>{
//         "\"123\" 123 \"海琛\" ",
//         {
//             {TokenType::STR_CONST,  "123"},
//             {TokenType::INT_CONST,  "123"},
//             {TokenType::STR_CONST,  "海琛"},
//         }
//     }
// ));


// class Test_SM_Position: public testing::TestWithParam<std::tuple<
//     std::string, 
//     std::vector<Token>, 
//     std::vector<hdg::Position>
// >>{};
// TEST_P(Test_SM_Position, _1){
//     using namespace sml;

//     auto [code, expected_token, expected_pos] = GetParam();

//     Sender s{};
//     auto ctx = std::make_shared<Context>(code);

//     sm<LexerSM> sm{s};
//     ASSERT_EQ(sm.is(INIT), true);

//     while (ctx.get()->getPtr() < ctx.get()->size()){
//         char c1 = ctx.get()->getChar();
//         bool res = sendEvent(c1, sm, ctx);

//         // 某个状态的事件无法处理！
//         ASSERT_TRUE(res);
//     }

//     auto actual = ctx.get()->getTokenArr();

//     ASSERT_EQ(actual.size(), expected_pos.size());
//     for (int i=0; i<actual.size(); i++){
//         EXPECT_EQ(actual[i].getType(), expected_token[i].getType());
//         EXPECT_EQ(actual[i].getVal(),  expected_token[i].getVal());
//         EXPECT_TRUE(actual[i].thisPosition().equal(expected_pos[i]));
//     }
// }

// hdg::Position buildPos(hdg::Indicator start, hdg::Indicator end){
//     hdg::Position pos;
//     pos.setStart(start);
//     pos.setEnd(end);
//     return pos;
// }

// INSTANTIATE_TEST_SUITE_P(TestSuit, Test_SM_Position, testing::Values(
//     std::tuple<std::string, std::vector<Token>, std::vector<hdg::Position>>{
//         "{}123 ",
//         {
//             {TokenType::BRACKET_T , "{"},
//             {TokenType::BRACKET_T , "}"},
//             {TokenType::INT_CONST , "123"}
//         },
//         {
//             buildPos({0,1,1},{1,1,2}),
//             buildPos({1,1,2},{2,1,3}),
//             buildPos({2,1,3},{5,1,6})
//         }
//     },
//     std::tuple<std::string, std::vector<Token>, std::vector<hdg::Position>>{
//         "{}123\n1 ",
//         {
//             {TokenType::BRACKET_T , "{"},
//             {TokenType::BRACKET_T , "}"},
//             {TokenType::INT_CONST , "123"},
//             {TokenType::INT_CONST , "1"}
//         },
//         {
//             buildPos({0,1,1},{1,1,2}),
//             buildPos({1,1,2},{2,1,3}),
//             buildPos({2,1,3},{5,1,6}),
//             buildPos({6,2,1},{7,2,2})
//         }
//     },
//     std::tuple<std::string, std::vector<Token>, std::vector<hdg::Position>>{
//         "{ \n function \n 1}",
//         {
//             {TokenType::BRACKET_T , "{"},
//             {TokenType::KEYWORD   , "function"},
//             {TokenType::INT_CONST , "1"},
//             {TokenType::BRACKET_T , "}"}
//         },
//         {
//             buildPos({0,1,1} ,{1,1,2}),
//             buildPos({4,2,2} ,{12,2,10}),
//             buildPos({15,3,2},{16,3,3}),
//             buildPos({16,3,3},{17,3,4})
//         }
//     }
// ));