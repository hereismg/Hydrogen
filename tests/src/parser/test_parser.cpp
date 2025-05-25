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

class Function_TEST_P: public testing::TestWithParam<std::tuple<int, std::string, int64_t>>{};
TEST_P(Function_TEST_P, _1){
    auto [counter, code, expected_obj] = GetParam();

    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // 这将来要弃用

    Parser parser(tokens, &envir2);

    auto unit = parser.new_ExeUnit();

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

/**********************************************
 * Basic Arithmetic
 **********************************************/

TEST(BasicArithmetic, _1){
    cout << "Hello World!" << endl;
}