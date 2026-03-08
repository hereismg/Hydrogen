#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <sml.hpp>
#include <gtest/gtest.h>

#include <kernel/Lexer.h>
#include <kernel/Parser.h> 
#include <basic/Environment.h>
#include <basic/Token.h>
#include <node/ObjectNode.h>
#include <node/Node.h>
#include <node/expr.h>
#include <node/stmt_node.h>
#include <node/unit_node.h>
#include <node/visitor.h>
#include <object/Function.h>
#include <object/List.h>
#include <object/Integer.h>
#include <object/Float.h>
#include <object/state_machine.h>

using namespace std;
using namespace hdg;

/**********************************************
 * Test 1. BinOperNode
 **********************************************/

class Expr_TEST_P: public testing::TestWithParam<std::tuple<
    std::string, // 测试标记（调试时通过该值定位测试点）
    sNode,       // 测试表达式，注意，这里是 共享指针
    sObject      // 预期测试结果
>>{};
TEST_P(Expr_TEST_P, _){
    auto [id, expr, expected] = GetParam();
    
    InterpreterVisitor visitor;
    
    expr->accept(visitor);
    
    auto actual = visitor.getRVal();
    
    if (!actual->equation(expected)->isTrue()){
        cout << "actual  : " << actual->toString()   << endl;
        cout << "expected: " << expected->toString() << endl;
        ASSERT_TRUE(false);
    }
}

INSTANTIATE_TEST_SUITE_P(BinOperNode_Arithmetic, Expr_TEST_P, testing::Values(
    tuple<string, sNode, sObject>{
        "1", 
        sNode(BinOperNode::createPlus(5, 2)),
        Integer::from(7)
    },

    tuple<string, sNode, sObject>{
        "2", 
        sNode(
            BinOperNode::createPlus(
                IntNode::create(3),
                BinOperNode::createPlus(2, 5)
            )
        ),
        Integer::from(10)
    },

    tuple<string, sNode, sObject>{
        "3", 
        sNode(
            BinOperNode::createMinus(5, 2)
        ),
        Integer::from(3)
    },

    tuple<string, sNode, sObject>{
        "1", 
        sNode(
            BinOperNode::createMul(5, 2)
        ),
        Integer::from(10)
    },

    tuple<string, sNode, sObject>{
        "1", 
        sNode(
            BinOperNode::createDiv(5, 2)
        ),
        Integer::from(2)
    },

    tuple<string, sNode, sObject>{
        /**
         * Expr:
         *     3 - (10 + 2) * 3 = -27
         *
         * AST:
         *        [ - ]
         *       /     \
         *    [ 3 ]    [ * ]
         *            /     \
         *        [ + ]     [ 3 ]
         *        /   \
         *    [10]   [ 2 ]
         */
        "1", 
        sNode( 
            BinOperNode::createMinus(
                IntNode::create(3),
                BinOperNode::createMul(
                    BinOperNode::createPlus(8, 2),
                    IntNode::create(3)
                )
            )
        ),
        Integer::from(-27)
    }
));


/**********************************************
 * Test 2. DefNode
 **********************************************/

TEST(test_DefNode, _1){
    uNode obj = std::make_unique<IntNode>(10);
    std::string name = "num";

    uNode assign = std::make_unique<DefNode>(name, std::move(obj));

    InterpreterVisitor visitor;

    assign->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    Object* obj_ptr = envir->getSymbol(name).get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 10);
}


/**********************************************
 * Test 3. ExeUnitNode
 **********************************************/

TEST(test_ExeUnitNode, _1){
    /**
     * var a = 1
     * var b = 2 + 3
     */
    uNode stmt1 = DefNode::create("a", IntNode::create(1));
    uNode stmt2 = DefNode::create("b", BinOperNode::createPlus(2, 3));
    
    // ExeUnitNode
    auto unit_node = std::make_unique<ExeUnitNode>();
    unit_node->getList().emplace_back(move(stmt1));
    unit_node->getList().emplace_back(move(stmt2));


    InterpreterVisitor visitor;

    unit_node->accept(visitor);

    // search symbol a, b
    {
        auto envir = visitor.getCurrentEnvir();
        Object* obj_ptr = envir->getSymbol("a").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 1);
    }
    {
        auto envir = visitor.getCurrentEnvir();
        Object* obj_ptr = envir->getSymbol("b").get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 5);
    }
}


/**********************************************
 * Test 4. IfStmtNode
 **********************************************/

TEST(test_IfStmtNode, _1){
    /**
     * if 1 {
     *     a = 1
     *     b = 2
     * }
     */
    // a = 1
    uNode int_node1 = std::make_unique<IntNode>(1);
    std::string name1 = "a";

    uNode assign_node1 = std::make_unique<DefNode>(name1, std::move(int_node1));

    // b = 2 + 3
    uNode int_node2 = std::make_unique<IntNode>(2);
    uNode int_node3 = std::make_unique<IntNode>(3);
    uNode oper_node = std::make_unique<BinOperNode>(
        Token(Token::Type::PLUS), 
        std::move(int_node2),
        std::move(int_node3)
    );
    std::string name2 = "b";
    uNode assign_node2 = std::make_unique<DefNode>(name2, std::move(oper_node));

    // ExeUnitNode
    std::unique_ptr<ExeUnitNode> unit_node = std::make_unique<ExeUnitNode>();
    unit_node->getList().emplace_back(std::move(assign_node1));
    unit_node->getList().emplace_back(std::move(assign_node2));

    // cond1
    uNode cond1 = std::make_unique<IntNode>(1);

    // if stmt
    auto ifStmt = std::make_unique<IfStmtNode>();

    ifStmt->addBranch(std::move(cond1), std::move(unit_node));

    InterpreterVisitor visitor;

    ifStmt->accept(visitor);

    // search symbol a, b
    {
        auto envir = visitor.getCurrentEnvir();
        Object* obj_ptr = envir->getSymbol(name1).get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 1);
    }
    {
        auto envir = visitor.getCurrentEnvir();
        Object* obj_ptr = envir->getSymbol(name2).get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 5);
    }
}

/**********************************************
 * Test 4. Function Obj
 **********************************************/

TEST(Base, FuncObj_1){
    /**
     * func add(a, b){
     *      a + b
     * }
     */
    std::vector<std::string> args_name = {"a", "b"};

    auto identA = std::make_unique<IdentNode>(args_name[0]);
    auto identB = std::make_unique<IdentNode>(args_name[1]);


    auto oper = std::make_unique<BinOperNode>(
        Token::Type::PLUS,
        std::move(identA),
        std::move(identB)
    );

    // 函数的环境应该由函数自己维护
    // visitor 和 envir 分离，因此 accept 应该要传入两个参数：visitor，envir
    // 那么，该怎么考虑环境的父子级关系？

    New_DefFunction func(args_name, std::move(oper));

    // 执行一次函数
    InterpreterVisitor visitor;
    auto num_1 = std::make_shared<Integer>(1);
    auto num_2 = std::make_shared<Integer>(2);
    func.parenthesis({num_1, num_2}, visitor);

    auto res = visitor.getResult().get();
    
    ASSERT_EQ(typeid(*res), typeid(Integer));

    Integer* int_ptr = dynamic_cast<Integer*>(res);

    ASSERT_EQ(int_ptr->getValue(), 3);
}

/**
 * fn add(a, b){
 *      a + b
 * }
 * 
 * add(1, 2)
 * 
 * PostfixNode(LPAREN, IntNode(1), IntNode(2))
*/

TEST(Smoke, PostfixNode_1){
    /**
     * func add(a, b){
     *      a + b
     * }
     */
    std::vector<std::string> args_name = {"a", "b"};

    auto identA = std::make_unique<IdentNode>(args_name[0]);
    auto identB = std::make_unique<IdentNode>(args_name[1]);

    auto oper = std::make_unique<BinOperNode>(
        Token::Type::PLUS,
        std::move(identA),
        std::move(identB)
    );

    auto func = std::make_shared<New_DefFunction>(args_name, std::move(oper));

    InterpreterVisitor visitor;
    auto envir = visitor.getCurrentEnvir();
    envir->setSymbol("add", func);
    
    // PostfixNode 
    // add(1, 2)
    auto ident = std::make_unique<IdentNode>("add");
    std::vector<uNode> args;
    args.emplace_back(std::make_unique<IntNode>(1));
    args.emplace_back(std::make_unique<IntNode>(2));
    auto postfix = PostfixNode::createParen(std::move(ident), std::move(args));

    // exe
    postfix->accept(visitor);

    // test
    {
        auto obj = visitor.getResult().get();

        ASSERT_NE(obj, nullptr);
        ASSERT_EQ(typeid(*obj), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj);

        ASSERT_EQ(int_ptr->getValue(), 3);
    }
}

TEST(Smoke, PostfixNode_2) {
    // 构造初始环境：list = [2025]
    auto list = std::make_shared<List>();
    list->getList().emplace_back(std::make_shared<Integer>(2025));

    InterpreterVisitor visitor;
    visitor.getCurrentEnvir()->setSymbol("list", list);

    // 构造 PostfixNode：list[0]
    auto ident = IdentNode::create("list");
    std::vector<uNode> exprList;
    exprList.emplace_back(IntNode::create(0));
    auto postfix = PostfixNode::createBracket(move(ident), move(exprList));

    // 执行
    postfix->accept(visitor);
    auto res = visitor.getResult();

    // 验证
    ASSERT_TRUE(res->equation(std::make_shared<Integer>(2025))->isTrue());
}

TEST(PostfixNodeTest, from_NullInputReturnsNullopt){
    uNode nullNode = nullptr;
    auto res = PostfixNode::from(move(nullNode));
    ASSERT_FALSE(res.has_value());
}

/**
 * list = [1, 2]
 * list.append(3)
 */
TEST(PostfixNodeTest, Dot_1){
    // list = [1, 2]
    auto list = List::from({1, 2});
    InterpreterVisitor visitor;
    visitor.getCurrentEnvir()->setSymbol("list", list);

    /**
     * hdg:
     *     list.append(3)
     * 
     * AST:
     *     __class__: PostfixNode
     *     
    */
    vector<uNode> args;
    args.emplace_back(IntNode::create(3));
    auto postfix = PostfixNode::createDotFun(IdentNode::create("list"), "append", move(args));

    // visitor
    postfix->accept(visitor);

    // judge
    auto actual = visitor.getResult();
    auto expected = List::from({1, 2});

    ASSERT_FALSE(expected->equation(actual)->isTrue());

    expected->append(3);

    ASSERT_TRUE(expected->equation(actual)->isTrue());
}

TEST(PostfixNodeTest, Dot_2){
    // list = [1, 2]
    auto list = List::from({1, 2});
    InterpreterVisitor visitor;
    visitor.getCurrentEnvir()->setSymbol("list", list);

    /**
     * hdg:
     *     list.insert(1, 2025)
     * 
     * AST:
     *     __class__: PostfixNode
     *     
    */
    vector<uNode> args;
    args.emplace_back(IntNode::create(1));
    args.emplace_back(IntNode::create(2025));
    auto postfix = PostfixNode::createDotFun(IdentNode::create("list"), "insert", move(args));

    postfix->accept(visitor);

    // judge
    auto res = List::from(visitor.getResult());

    ASSERT_TRUE(visitor.getResult()->equation(
        List::from({1, 2025, 2})
    )->isTrue());
}


// /**
//  * list = [1, 2]
//  * list.pop()
//  */
// TEST(PostfixNodeTest, Dot_2){
//     // list = [1, 2]
//     auto list = std::make_shared<List>();
//     list->append(1)
//         ->append(2);

//     InterpreterVisitor visitor;
//     visitor.getCurrentEnvir()->setSymbol("list", list);

//     // list.append(3)
//     auto primary = std::make_unique<IdentNode>("list");
//     std::vector<uNode> exprList;
//     exprList.emplace_back(std::make_unique<IntNode>(3));
//     auto postfix = std::make_unique<PostfixNode>(Token::DOT, std::move(primary), "append", std::move(exprList));

//     // visitor
//     postfix->accept(visitor);

//     // judge
//     auto expected = std::make_shared<List>();
//     expected->append(1)
//             ->append(2)
//             ->append(3);
//     auto actual = visitor.getResult();

//     ASSERT_TRUE(expected->equation(actual)->isTrue());
// }

// TEST(Smoke, ListObjNode_1) {
//     // 构造初始环境：list = [2025]
//     auto list = std::make_shared<List>();
//     list->getList().emplace_back(std::make_shared<Integer>(2025));

//     InterpreterVisitor visitor;
//     visitor.getCurrentEnvir()->setSymbol("list", list);

//     // 构造 PostfixNode：list[0]
//     auto ident = std::make_unique<IdentNode>("list");
//     std::vector<uNode> exprList;
//     exprList.emplace_back(std::make_unique<IntNode>(0));
//     auto postfix = std::make_unique<PostfixNode>(
//         Token::Type::LBRACKET,
//         std::move(ident),
//         std::move(exprList)
//     );

//     // 执行
//     postfix->accept(visitor);
//     auto res = visitor.getResult();

//     // 验证
//     ASSERT_TRUE(res->equation(std::make_shared<Integer>(2025))->isTrue());
// }