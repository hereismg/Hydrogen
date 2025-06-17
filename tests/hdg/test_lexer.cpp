#include <memory>

#include <sml.hpp>
#include <gtest/gtest.h>

#include <kernel/Lexer.h>
#include <kernel/Parser.h> 
#include <basic/Environment.h>
#include <node/ObjectNode.h>
#include <node/expr.h>
#include <node/stmt_node.h>
#include <node/unit_node.h>
#include <object/Integer.h>

using namespace std;
using namespace hdg;

typedef enum{
    LOW,  // 只要求 Token 的 type 匹配
    MID,  // 要求 Token 的 type 和 value 同时匹配
    HIGH  // 要求 Token 的 type、value 和 pos 三个同时匹配
} Degree;

class Lexer_TEST_P: public testing::TestWithParam<std::tuple<
    std::string,             // 测试标记（调试时通过该值定位测试点）
    std::string,             // 代码
    std::vector<hdg::Token>, // 预期结果
    Degree                   // 检查严格度
>>{};
TEST_P(Lexer_TEST_P, _){
    auto [anchor, code, expected, degree] = GetParam();

    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> actual = lexer.run(path, &code);

    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); i++){
        ASSERT_EQ(actual[i].getType(), expected[i].getType());

        if (degree >= MID) {
            ASSERT_EQ(actual[i].getValue(), expected[i]. getValue());
        }

        if (degree >= HIGH) {
            ASSERT_TRUE(actual[i].thisPosition()->equal(*expected[i].thisPosition()));
        }
    }
}

INSTANTIATE_TEST_SUITE_P(TestSuit, Lexer_TEST_P, testing::Values(
tuple<string, string, vector<Token>, Degree>{
"1",
"a = 1",
{
    {Token::IDENT , "a"},
    {Token::EQ    , "" },
    {Token::INT   , "1"},
    {Token::EF    , "" }
},
MID
},

tuple<string, string, vector<Token>, Degree>{
"1",
"a[1]",
{
    {Token::IDENT    , "a"},
    {Token::LBRACKET , "" },
    {Token::INT      , "1"},
    {Token::RBRACKET , "" },
    {Token::EF       , "" }
},
MID
},

tuple<string, string, vector<Token>, Degree>{
"1",
"var list = [1, 2]",
{
    {Token::KEYWORD  , "var" },
    {Token::IDENT    , "list"},
    {Token::EQ       , ""    },
    {Token::LBRACKET , ""    },
    {Token::INT      , "1"   },
    {Token::COMMA    , ""    },
    {Token::INT      , "2"   },
    {Token::RBRACKET , ""    },
    {Token::EF       , ""    }
},
MID
}

));

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
    expected_tokens.emplace_back(hdg::Token::IDENT, "n");
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


class Test_Template: public testing::TestWithParam<std::tuple<int, std::string, int64_t>>{};
TEST_P(Test_Template, AssignStmt_2){
    auto [counter, code, expected_obj] = GetParam();

    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    auto unit = parser.exeUnit();

    ASSERT_NE(unit, nullptr);

    InterpreterVisitor visitor;
    unit->accept(visitor);

    {
        auto obj = visitor.getResult().get();

        ASSERT_NE(obj, nullptr);
        ASSERT_EQ(typeid(*obj), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj);

        ASSERT_EQ(int_ptr->getValue(), expected_obj);
    }
}

INSTANTIATE_TEST_SUITE_P(Smoke, Test_Template, testing::Values(
std::tuple<int, std::string, int64_t>{
0,
R"({
    var a = 1
    var b = a
    a = 2
    b
})",
1
}
));

TEST(test_ExeUnit, _1){
    string code = "{var a = 1; var b = 2}";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.exeUnit();

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
    var a = 1
    var b = 2
}
    )";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.exeUnit();

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
    var a = 1
    var b = a + 3
    b
}
    )";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.exeUnit();

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


TEST(Base, IfStmt_1){
    string code = R"({
    if 1 {
        var a = 1
        var b = a + 1
    }
    b
}
    )";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode ast = parser.exeUnit();

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

TEST(Smoke, params_3){
    string code = 
R"(

)";
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    auto params = parser.new_Params();

    ASSERT_EQ(params.size(), 0);
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

    auto assignFunc = parser.funcDef();

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
    auto ident = std::make_unique<IdentNode>("add");
    auto postfix = PostfixNode::createParen(move(ident), move(args));

    postfix->accept(visitor);

    {
        auto obj = visitor.getResult().get();

        ASSERT_NE(obj, nullptr);
        ASSERT_EQ(typeid(*obj), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj);

        ASSERT_EQ(int_ptr->getValue(), 3);
    }
}



class Function_TEST_P: public testing::TestWithParam<std::tuple<int, std::string, int64_t>>{};
TEST_P(Function_TEST_P, _1){
    auto [counter, code, expected_obj] = GetParam();

    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    auto unit = parser.exeUnit();
    // cout << unit->toJSON().dump(4) << endl;

    ASSERT_NE(unit, nullptr);

    InterpreterVisitor visitor;
    unit->accept(visitor);

    {
        auto obj = visitor.getRVal().get();

        ASSERT_NE(obj, nullptr);
        ASSERT_EQ(typeid(*obj), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj);

        ASSERT_EQ(int_ptr->getValue(), expected_obj);
    }
}
int counter = 0;
INSTANTIATE_TEST_SUITE_P(Smoke, Function_TEST_P, testing::Values(
// std::tuple<int, std::string, int64_t>{
// counter ++,
// R"({
//     var sum = 0
//     function fun(a) {
//         if a {
//             sum = sum + fun(a - 1)
//         }
//         a
//     }
//     sum = fun(5)
//     sum
// })",
// 15
// },

// std::tuple<int, std::string, int64_t>{
// counter ++,
// R"({
// PLUS = 1
// MINE = 2

// function oper(oper) {
//     function plus(a, b){
//         a + b
//     }

//     function mine(a, b){
//         a - b
//     }
    
//     if oper == PLUS {
//         plus
//     }
//     elif oper == MINE {
//         mine
//     }
// }

// myOper = oper(PLUS)
// myOper(1, 2)
// })",
// 3
// },

// std::tuple<int, std::string, int64_t>{
// counter ++,
// R"({
//     function oper(){
//         function add(a, b){
//             a + b
//         }
//         add
//     }
//     oper()(1, 2)
// })",
// 3
// },

// std::tuple<int, std::string, int64_t>{
// counter ++,
// R"({
//     var list = [2, 3]
//     function add(pair){
//         var a = list[0]
//         var b = list[1]
//         list[0] = a + b
//         list[1] = a - b
//     }
//     list[0] + list[1]
// })",
// 4
// },

std::tuple<int, std::string, int64_t>{
counter ++,
R"({
    function add(pair){
        pair[0] + pair[1]
    }
    add([1, 2])
})",
3
}
));


/*
add


{
    "type (Token::Type)": {

    }
    primary = ...
    ident ...
    exprList ...
}

add()
add()()
add[]()

{
    "__class__" : "PostfixNode",
    "ident"     : "$nullptr",
    "primary"   : {
            "__class__" : "PostfixNode",
            "ident"     : "add",
            "primary"   : "$nullptr",
            "type"      : "$Token::Type::RPAREN",
        },
    "type" : "$Token::Type::RPAREN",
}

{
    "__class__" : "PostfixNode",
    "type"      : "$Token::Type::LPAREN",   // ()
    "primary"   : {
            "__class__" : "PostfixNode",
            "type"      : "$Token::Type::LPAREN",
            "primary"   : {
                "__class__" : "IdentNode",
                "val"       : "add"
            }
        },
}

getList()[0] = 1

{
    "__class__" : "AssignNode",
    "lVal" : {
        "__class__" : "PostfixNode",
        "type" : "$Token::Type::LPAREN"   // ()
    },
    "rVal" : {
        "__class__" : "IntNode",
        "val" : 1,
    }
}


PostfixExpr   : Primary { PostfixSuffix }
PostfixSuffix : '(' ExprList ')'
              | '[' ExprList ']'
              | '.' IDENT '(' ExprList ')'
Primary       : INT_CONST          
              | FLOAT_CONST        
              | STR_CONST          
              | IDENT              
              | '(' ArithExpr ')'  


           
Primary    : INT_CONST          IntNode        Integer
           | FLOAT_CONST        FloatNode      Float
           | STR_CONST          StrNode        String
           | IDENT              IdentNode      Object    在 Envri 中寻找该标识符
           | '(' ArithExpr ')'  BinOperNode    Object    根据运算符计算

INT_CONST | IDENT
(INT_CONST | IDENT) | PostfixExpr '(' ExprList ')' | PostfixExpr '[' ExprList ']' | PostfixExpr '.' IDENT '(' ExprList ')'
*/