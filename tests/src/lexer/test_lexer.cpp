#include <memory>

#include <sml.hpp>
#include <gtest/gtest.h>

#include <Lexer.h>
#include <Environment.h>
#include <Parser.h>
#include <ObjectNode.h>
#include <BinaryOperatorNode.h>

using namespace std;
using namespace hdg;

TEST(test_lexer, _1){
    string code = "if";
    string path = "<stdin>";
    Lexer lexer;

    auto actual_tokens = lexer.run(path, &code);

    std::vector<hdg::Token> expected_tokens;
    expected_tokens.emplace_back(hdg::Token::KEYWORD, "if");
    expected_tokens.emplace_back(hdg::Token::EF);

    ASSERT_EQ(actual_tokens.size(), expected_tokens.size());
    for (int i=0; i<expected_tokens.size(); i++){
        ASSERT_EQ(expected_tokens[i].getType(), actual_tokens[i].getType());
        ASSERT_EQ(expected_tokens[i].getValue(), actual_tokens[i].getValue());
    }
}

TEST(test_lexer, _2){
    string code = "1";
    string path = "<stdin>";
    Lexer lexer;

    auto actual_tokens = lexer.run(path, &code);

    std::vector<hdg::Token> expected_tokens;
    expected_tokens.emplace_back(hdg::Token::INT, "1");
    expected_tokens.emplace_back(hdg::Token::EF);

    ASSERT_EQ(actual_tokens.size(), expected_tokens.size());
    for (int i=0; i<expected_tokens.size(); i++){
        ASSERT_EQ(expected_tokens[i].getType(), actual_tokens[i].getType());
        ASSERT_EQ(expected_tokens[i].getValue(), actual_tokens[i].getValue());
    }
}

TEST(test_lexer, _3){
    string code = "if n == 1 {}";
    string path = "<stdin>";
    Lexer lexer;

    auto actual_tokens = lexer.run(path, &code);

    std::vector<hdg::Token> expected_tokens;
    expected_tokens.emplace_back(hdg::Token::KEYWORD,    "if");
    expected_tokens.emplace_back(hdg::Token::IDENTIFIER, "n");
    expected_tokens.emplace_back(hdg::Token::EE);
    expected_tokens.emplace_back(hdg::Token::INT,        "1");
    expected_tokens.emplace_back(hdg::Token::LBRACE);
    expected_tokens.emplace_back(hdg::Token::RBRACE);
    expected_tokens.emplace_back(hdg::Token::EF);

    ASSERT_EQ(actual_tokens.size(), expected_tokens.size());
    for (int i=0; i<expected_tokens.size(); i++){
        ASSERT_EQ(expected_tokens[i].getType(), actual_tokens[i].getType());
        ASSERT_EQ(expected_tokens[i].getValue(), actual_tokens[i].getValue());
    }
}

TEST(test_kv_toString, _1){
    {
        auto str = kv_toString("INT", 8, "2025", 128);
        cout << str << endl;
        ASSERT_EQ(str, "INT      : 2025");
    }
    {
        auto str = kv_toString("STRING", 8, "Hello World!\tSecond!\r\n", 128);
        cout << str << endl;
        ASSERT_EQ(str, "STRING   : Hello World!\\tSecond!\\r\\n");
    }
}

TEST(test_kv_toString, _2){
    {
        auto str = kv_toString("STRING", 8, "Hello World!", 8);
        cout << str << endl;
        ASSERT_EQ(str, "STRING   : Hello Wo...");
    }
    {
        auto str = kv_toString("STRING", 8, "\n\t\r\n\t\r", 8);
        cout << str << endl;
        ASSERT_EQ(str, "STRING   : \\n\\t\\r\\n...");
    }
    {
        auto str = kv_toString("STRING", 8, "\n\t\r\n\t\r", 9);
        cout << str << endl;
        ASSERT_EQ(str, "STRING   : \\n\\t\\r\\n\\t..");
    }
    // {
    //     auto str = kv_toString("IDENTIFIER", 8, "\n\t\r\n\t\r", 9);
    //     cout << str << endl;
    //     ASSERT_EQ(str, "IDENTIFI... : \\n\\t\\r\\n\\t..");
    // }
}

TEST(test_Position, clone){
    string fPath = "<stdin>";
    string txt   = "a + b";
    Indicator start(1, 2, 3);
    Indicator end(2, 3, 4);

    Position pos(
        fPath,
        &txt,
        start,
        end
    );

    Position copy = pos.clone();

    copy.setStart({11, 22, 33});

    ASSERT_EQ(pos.getStart().col,   start.col);
    ASSERT_EQ(pos.getStart().index, start.index);
    ASSERT_EQ(pos.getStart().line,  start.line);
}

TEST(test_Parser, new_Primary){
    string code = "1";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir;

    Parser parser(tokens, &envir);

    uNode ast = parser.new_Primary();

    Integer* num = (Integer*)ast->interpret();

    ASSERT_EQ(num->getValue(), 1);
}

TEST(test_Parser, new_ArithExpr){
    string code = "1 + 1";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir;

    Parser parser(tokens, &envir);

    uNode ast = parser.new_Primary();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    Integer* num = (Integer*)ast->interpret();

    ASSERT_EQ(num->getValue(), 2);
}

TEST(test_BinOperNode, _1) {
    uNode left = std::make_unique<IntNode>(5);
    uNode right = std::make_unique<IntNode>(2);

    Token plus(Token::Type::PLUS);

    uNode expr = std::make_unique<BinOperNode>(
        std::move(plus),
        std::move(left),
        std::move(right)
    );

    InterpreterVisitor visitor;

    expr->accept(visitor);
}
