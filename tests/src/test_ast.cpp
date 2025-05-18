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

    auto& envir = visitor.getEnvironment();
    Object* obj_ptr = envir.getSymbol(name).get();

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
        auto& envir = visitor.getEnvironment();
        Object* obj_ptr = envir.getSymbol(name1).get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 1);
    }
    {
        auto& envir = visitor.getEnvironment();
        Object* obj_ptr = envir.getSymbol(name2).get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 5);
    }
}

uNode buildAssign_1(){
    uNode int_node1 = std::make_unique<IntNode>(1);
    std::string name1 = "a";

    uNode assign_node1 = std::make_unique<new_AssignNode>(name1, std::move(int_node1));
    
    return assign_node1;
}

TEST(test_ExeUnitNode, _1){
    // a = 1

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
        auto& envir = visitor.getEnvironment();
        Object* obj_ptr = envir.getSymbol(name1).get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 1);
    }
    {
        auto& envir = visitor.getEnvironment();
        Object* obj_ptr = envir.getSymbol(name2).get();

        ASSERT_EQ(typeid(*obj_ptr), typeid(Integer));

        Integer* int_ptr = dynamic_cast<Integer*>(obj_ptr);

        ASSERT_EQ(int_ptr->getValue(), 5);
    }
}