#include <memory>

#include <sml.hpp>
#include <gtest/gtest.h>

#include <Lexer.h>
#include <Environment.h>
#include <Parser.h>
#include <ObjectNode.h>
#include <BinaryOperatorNode.h>
#include <stmt_node.h>
#include <unit_node.h>

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

    InterpreterVisitor visitor;

    ast->accept(visitor);

    Object* obj_ptr = visitor.getResult().get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr= dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 1);
}

TEST(test_Parser, new_ArithExpr){ // hdgTodo: 使用 TEST_P
    string code = "1 + 1";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir;

    Parser parser(tokens, &envir);

    uNode ast = parser.new_ArithExpr();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    Object* obj_ptr = visitor.getResult().get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr= dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 2);
}

TEST(test_Parser, new_ArithExpr_2){
    string code = "1 + 1 - 3";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir;

    Parser parser(tokens, &envir);

    uNode ast = parser.new_ArithExpr();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    Object* obj_ptr = visitor.getResult().get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr= dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), -1);
}

TEST(test_Parser, new_ArithExpr_3){
    string code = "2 / 2 + 1 * 3";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir;

    Parser parser(tokens, &envir);

    uNode ast = parser.new_ArithExpr();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    Object* obj_ptr = visitor.getResult().get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr= dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 4);
}

TEST(test_Parser, new_ArithExpr_4){
    string code = "8 / 2 + (1) * 3";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir;

    Parser parser(tokens, &envir);

    uNode ast = parser.new_ArithExpr();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    Object* obj_ptr = visitor.getResult().get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr= dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 7);
}


TEST(test_Parser, new_ArithExpr_5){
    string code = "8 / (2 + 1) * 3";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir;

    Parser parser(tokens, &envir);

    uNode ast = parser.new_ArithExpr();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    Object* obj_ptr = visitor.getResult().get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr= dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 6);
}


TEST(test_AssignStmt, _1){
    string code = "a = 1";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.new_AssignStmt();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    Object* obj_ptr = envir->getSymbol("a").get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 1);
}

TEST(test_ExeUnit, _1){
    string code = "{a = 1; b = 2}";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.new_ExeUnit();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    Object* obj_ptr = envir->getSymbol("a").get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 1);
}

TEST(test_ExeUnit, _2){
    string code = R"({
    a = 1
    b = 2
}
    )";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.new_ExeUnit();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    {
        Object* obj_ptr = envir->getSymbol("a").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 1);
    }
    {
        Object* obj_ptr = envir->getSymbol("b").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 2);
    }
}

TEST(test_ExeUnit, _3){
    string code = R"({
    a = 1
    b = a + 3
    b
}
    )";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.new_ExeUnit();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    {
        Object* obj_ptr = envir->getSymbol("a").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 1);
    }
    {
        Object* obj_ptr = envir->getSymbol("b").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 4);
    }
    {
        Object* obj_ptr = visitor.getResult().get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 4);
    }
}


TEST(test_IfStmt, _1){
    string code = R"({
    if 1 {
        a = 1
        b = a + 1
    }
    b
}
    )";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.new_ExeUnit();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    {
        Object* obj_ptr = envir->getSymbol("a").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 1);
    }
    {
        Object* obj_ptr = envir->getSymbol("b").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 2);
    }
    {
        Object* obj_ptr = visitor.getResult().get();

        ASSERT_NE(obj_ptr, nullptr);

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 2);
    }
}



TEST(test_WhileStmt, _1){
    string code = R"({
    counter = 5
    sum = 0
    while counter {
        sum = sum + counter
        counter = counter - 1
    }
    sum
}
    )";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.new_ExeUnit();

    InterpreterVisitor visitor;

    ast->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    {
        Object* obj_ptr = visitor.getResult().get();

        ASSERT_NE(obj_ptr, nullptr);

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 15);
    }
}

TEST(Smoke, params_1){
    string code = R"(a, b, c)";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    auto params = parser.new_Params();

    std::vector<std::string> expected = {"a", "b", "c"};

    ASSERT_EQ(params.size(), expected.size());

    for (size_t i = 0; i < expected.size(); i++){
        ASSERT_EQ(params[i], expected[i]);     
    }
}

TEST(Smoke, params_2){
    string code = 
R"(
a, 
b, 
c
)";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    auto params = parser.new_Params();

    std::vector<std::string> expected = {"a", "b", "c"};

    ASSERT_EQ(params.size(), expected.size());

    for (size_t i = 0; i < expected.size(); i++){
        ASSERT_EQ(params[i], expected[i]);     
    }
}

TEST(Smoke, funcDef_1){
    string code = 
R"(
function add(a, b){
    a + b
}
)";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    auto assignFunc = parser.new_FuncDef();

    ASSERT_NE(assignFunc, nullptr);

    InterpreterVisitor visitor;
    assignFunc->accept(visitor);

    // 检查 add 是否存在
    auto funObj = visitor.getCurrentEnvir()->getSymbol("add");
    ASSERT_NE(funObj, nullptr);

    // add(1, 2)
    std::vector<uNode> args;
    args.emplace_back(std::make_unique<IntNode>(1));
    args.emplace_back(std::make_unique<IntNode>(2));
    auto postfix = std::make_unique<PostfixNode>(Token::Type::LPAREN, "add", std::move(args), Position());

    postfix->accept(visitor);

    {
        auto obj = visitor.getResult().get();

        ASSERT_NE(obj, nullptr);
        ASSERT_EQ(typeid(*obj), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj);

        ASSERT_EQ(int_ptr->getValue(), 3);
    }
}

TEST(Smoke, funcDef_2){
    string code = 
R"(
{
    function add(a, b){
            a + b
    }
    add(1, 2)
}
)";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    // auto unit = parser.new_ExeUnit();

    // ASSERT_NE(unit, nullptr);

    // InterpreterVisitor visitor;
    // unit->accept(visitor);

    // {
    //     auto obj = visitor.getResult().get();

    //     ASSERT_NE(obj, nullptr);
    //     ASSERT_EQ(typeid(*obj), typeid(Integer));

    //     Integer* int_ptr = dynamic_cast<Integer*>(obj);

    //     ASSERT_EQ(int_ptr->getValue(), 3);
    // }
}
