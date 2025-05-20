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
#include <Function.h>

using namespace std;
using namespace hdg;

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

    ASSERT_EQ(typeid(*visitor.getResult().get()), typeid(Integer));

    Integer* res = dynamic_cast<Integer*>(visitor.getResult().get());

    ASSERT_EQ(res->getValue(), 7);
}

TEST(test_BinOperNode, _2) {
    /*
       BinOperNode(2)
        /       \
    Integer(3)   BinOperNode(1)
                 /         \
           Integer(1)       Integer(2)
    */
    uNode int1 = std::make_unique<IntNode>(5);
    uNode int2 = std::make_unique<IntNode>(2);

    Token plus1(Token::Type::PLUS);

    uNode binOper1 = std::make_unique<BinOperNode>(
        std::move(plus1),
        std::move(int1),
        std::move(int2)
    );

    uNode int3 = std::make_unique<IntNode>(3);

    Token plus2(Token::Type::PLUS);

    uNode binOper2 = std::make_unique<BinOperNode>(
        std::move(plus2),
        std::move(int3),
        std::move(binOper1)
    );

    InterpreterVisitor visitor;

    binOper2->accept(visitor);

    ASSERT_EQ(typeid(*visitor.getResult().get()), typeid(Integer));

    Integer* res = dynamic_cast<Integer*>(visitor.getResult().get());

    ASSERT_EQ(res->getValue(), 10);
}

TEST(test_BinOperNode, _3) {
    uNode left = std::make_unique<IntNode>(5);
    uNode right = std::make_unique<IntNode>(2);

    Token oper(Token::Type::MINUS);

    uNode expr = std::make_unique<BinOperNode>(
        std::move(oper),
        std::move(left),
        std::move(right)
    );

    InterpreterVisitor visitor;

    expr->accept(visitor);

    ASSERT_EQ(typeid(*visitor.getResult().get()), typeid(Integer));

    Integer* res = dynamic_cast<Integer*>(visitor.getResult().get());

    ASSERT_EQ(res->getValue(), 3);
}


TEST(test_BinOperNode, _4) {
    uNode left = std::make_unique<IntNode>(5);
    uNode right = std::make_unique<IntNode>(2);

    Token oper(Token::Type::MUL);

    uNode expr = std::make_unique<BinOperNode>(
        std::move(oper),
        std::move(left),
        std::move(right)
    );

    InterpreterVisitor visitor;

    expr->accept(visitor);

    ASSERT_EQ(typeid(*visitor.getResult().get()), typeid(Integer));

    Integer* res = dynamic_cast<Integer*>(visitor.getResult().get());

    ASSERT_EQ(res->getValue(), 10);
}

TEST(test_BinOperNode, _5) {
    uNode left = std::make_unique<IntNode>(5);
    uNode right = std::make_unique<IntNode>(2);

    Token oper(Token::Type::DIV);

    uNode expr = std::make_unique<BinOperNode>(
        std::move(oper),
        std::move(left),
        std::move(right)
    );

    InterpreterVisitor visitor;

    expr->accept(visitor);

    ASSERT_EQ(typeid(*visitor.getResult().get()), typeid(Integer));

    Integer* res = dynamic_cast<Integer*>(visitor.getResult().get());

    ASSERT_EQ(res->getValue(), 2);
}

TEST(test_BinOperNode, _6) {
    /*
       BinOperNode-2
        /       \
  Integer-3     BinOperNode-1
                 /         \
           Integer-1       Integer-2
    */
    uNode int1 = std::make_unique<IntNode>(5);
    uNode int2 = std::make_unique<IntNode>(2);

    Token oper1(Token::Type::PLUS);

    uNode binOper1 = std::make_unique<BinOperNode>(
        std::move(oper1),
        std::move(int1),
        std::move(int2)
    );

    uNode int3 = std::make_unique<IntNode>(3);

    Token oper2(Token::Type::MINUS);

    uNode binOper2 = std::make_unique<BinOperNode>(
        std::move(oper2),
        std::move(int3),
        std::move(binOper1)
    );

    InterpreterVisitor visitor;

    binOper2->accept(visitor);

    ASSERT_EQ(typeid(*visitor.getResult().get()), typeid(Integer));

    Integer* res = dynamic_cast<Integer*>(visitor.getResult().get());

    ASSERT_EQ(res->getValue(), -4);
}

TEST(test_BinOperNode, _7) {
    /*
        BinOperNode-3
         /         \
  Integer-4       BinOperNode-2
                   /         \
          BinOperNode-1       Integer-3
           /       \
    Integer-1     Integer-2
    
    */
    uNode int1 = std::make_unique<IntNode>(10);
    uNode int2 = std::make_unique<IntNode>(2);

    Token oper1(Token::Type::PLUS);

    uNode binOper1 = std::make_unique<BinOperNode>(
        std::move(oper1),
        std::move(int1),
        std::move(int2)
    );

    uNode int3 = std::make_unique<IntNode>(3);

    Token oper2(Token::Type::MINUS);

    uNode binOper2 = std::make_unique<BinOperNode>(
        std::move(oper2),
        std::move(binOper1),
        std::move(int3)
    );

    uNode int4 = std::make_unique<IntNode>(5);

    Token oper3(Token::Type::MUL);

    uNode binOper3 = std::make_unique<BinOperNode>(
        std::move(oper3),
        std::move(int4),
        std::move(binOper2)
    );

    InterpreterVisitor visitor;

    binOper3->accept(visitor);

    ASSERT_EQ(typeid(*visitor.getResult().get()), typeid(Integer));

    Integer* res = dynamic_cast<Integer*>(visitor.getResult().get());

    ASSERT_EQ(res->getValue(), 45);
}

TEST(test_AssignNode, _1){
    uNode obj = std::make_unique<IntNode>(10);
    std::string name = "num";

    uNode assign = std::make_unique<new_AssignNode>(name, std::move(obj));

    InterpreterVisitor visitor;

    assign->accept(visitor);

    auto envir = visitor.getCurrentEnvir();
    Object* obj_ptr = envir->getSymbol(name).get();

    ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

    Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

    ASSERT_EQ(int_ptr->getValue(), 10);
}


TEST(test_ExeUnitNode, _1){
    // a = 1
    uNode int_node1 = std::make_unique<IntNode>(1);
    std::string name1 = "a";

    uNode assign_node1 = std::make_unique<new_AssignNode>(name1, std::move(int_node1));

    // b = 2 + 3
    uNode int_node2 = std::make_unique<IntNode>(2);
    uNode int_node3 = std::make_unique<IntNode>(3);
    uNode oper_node = std::make_unique<BinOperNode>(
        Token(Token::Type::PLUS), 
        std::move(int_node2),
        std::move(int_node3)
    );
    std::string name2 = "b";
    uNode assign_node2 = std::make_unique<new_AssignNode>(name2, std::move(oper_node));

    // ExeUnitNode
    std::unique_ptr<new_ExeUnitNode> unit_node = std::make_unique<new_ExeUnitNode>();
    unit_node->getList().emplace_back(std::move(assign_node1));
    unit_node->getList().emplace_back(std::move(assign_node2));


    InterpreterVisitor visitor;

    unit_node->accept(visitor);

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

    uNode assign_node1 = std::make_unique<new_AssignNode>(name1, std::move(int_node1));

    // b = 2 + 3
    uNode int_node2 = std::make_unique<IntNode>(2);
    uNode int_node3 = std::make_unique<IntNode>(3);
    uNode oper_node = std::make_unique<BinOperNode>(
        Token(Token::Type::PLUS), 
        std::move(int_node2),
        std::move(int_node3)
    );
    std::string name2 = "b";
    uNode assign_node2 = std::make_unique<new_AssignNode>(name2, std::move(oper_node));

    // ExeUnitNode
    std::unique_ptr<new_ExeUnitNode> unit_node = std::make_unique<new_ExeUnitNode>();
    unit_node->getList().emplace_back(std::move(assign_node1));
    unit_node->getList().emplace_back(std::move(assign_node2));

    // cond1
    uNode cond1 = std::make_unique<IntNode>(1);

    // if stmt
    auto ifStmt = std::make_unique<new_IfStmtNode>();

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

TEST(test_FuncObj, _1){
    uNode int1 = std::make_unique<IntNode>(10);
    uNode int2 = std::make_unique<IntNode>(2);

    Token oper1(Token::Type::PLUS);

    uNode binOper1 = std::make_unique<BinOperNode>(
        std::move(oper1),
        std::move(int1),
        std::move(int2)
    );

    uNode int3 = std::make_unique<IntNode>(3);

    Token oper2(Token::Type::MINUS);

    uNode binOper2 = std::make_unique<BinOperNode>(
        std::move(oper2),
        std::move(binOper1),
        std::move(int3)
    );

    uNode int4 = std::make_unique<IntNode>(5);

    Token oper3(Token::Type::MUL);

    uNode binOper3 = std::make_unique<BinOperNode>(
        std::move(oper3),
        std::move(int4),
        std::move(binOper2)
    );

    // 函数的环境应该由函数自己维护
    // visitor 和 envir 分离，因此 accept 应该要传入两个参数：visitor，envir
    // 那么，该怎么考虑环境的父子级关系？

    New_DefFunction(std::vector<std::string>(), std::move(binOper3));


    InterpreterVisitor visitor;
}

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

TEST(Base, PostfixNode_1){
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
    std::vector<uNode> args;
    args.emplace_back(std::make_unique<IntNode>(1));
    args.emplace_back(std::make_unique<IntNode>(2));
    auto postfix = std::make_unique<PostfixNode>(Token::Type::LPAREN, "add", std::move(args), Position());

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