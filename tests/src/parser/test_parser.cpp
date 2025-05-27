#include <gtest/gtest.h>
#include <Lexer.h>
#include <sml.hpp>
#include <memory>

#include <Lexer.h>
#include <Environment.h>
#include <Parser.h>
#include <ObjectNode.h>
#include <BinaryOperatorNode.h>
#include <stmt_node.h>
#include <unit_node.h>

using namespace std;
using namespace hdg;

typedef enum {
    Expr,
    IfStmt,
    ExeUnit
} ParserType;
class Interepreter_TEST_P: public testing::TestWithParam<std::tuple<
    int,            // 序号
    std::string,    // 代码
    int64_t,        // 执行的结果
    ParserType      // 执行函数
>>{};

TEST_P(Interepreter_TEST_P, _){
    auto [counter, code, expected, parserType] = GetParam();

    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode root;
    switch (parserType) {
    case ParserType::Expr : 
        root = parser.new_Expr();
        break;
    case ParserType::IfStmt :
        root = parser.new_IfStmt();
        break;
    case ParserType::ExeUnit :
        root = parser.new_ExeUnit();
        break;
    default:
        ASSERT_TRUE(false);   
    }
    ASSERT_NE(root, nullptr);

    InterpreterVisitor visitor;
    root->accept(visitor);

    // 检测正确性，未使用 equation 方法
    auto obj = visitor.getRVal().get();

    ASSERT_NE(obj, nullptr);
    ASSERT_EQ(typeid(*obj), typeid(Integer));

    Integer* int_ptr = dynamic_cast<Integer*>(obj);

    ASSERT_EQ(int_ptr->getValue(), expected);
}

/**********************************************
 * 1. Expr
 **********************************************/

INSTANTIATE_TEST_SUITE_P(Expr_Arithmetic, Interepreter_TEST_P, testing::Values(
std::tuple<int, std::string, int64_t, ParserType>{
0,
"1 + 2",
3,
ParserType::Expr
},

std::tuple<int, std::string, int64_t, ParserType>{
1,
"1 + ( 2 + 3 ) * 4",
21,
ParserType::Expr
},

std::tuple<int, std::string, int64_t, ParserType>{
2,
"0 - 1",
-1,
ParserType::Expr
},

std::tuple<int, std::string, int64_t, ParserType>{
3,
"{var a = 1 var b = 2 a + b}",
3,
ParserType::ExeUnit
}
));


/**********************************************
 * 2. Execute Unit
 **********************************************/

/**********************************************
 * 3. Variable
 **********************************************/

/**********************************************
 * 4. Process Control
 **********************************************/

INSTANTIATE_TEST_SUITE_P(ProcessControl_IfStmt, Interepreter_TEST_P, testing::Values(
std::tuple<int, std::string, int64_t, ParserType>{
0,
R"(
if 1 + 1 {
    10
} else {
    5
}
)",
10,
ParserType::IfStmt
},

std::tuple<int, std::string, int64_t, ParserType>{
1,
R"(
if 
1 + 1 
{
    10
}
else {
    5
}
)",
10,
ParserType::IfStmt
},

std::tuple<int, std::string, int64_t, ParserType>{
2,
R"({
var a = 1
if a {
    a
}
else {
    a - 1
}
})",
1,
ParserType::ExeUnit
}

));

/**********************************************
 * 5. Function
 **********************************************/
