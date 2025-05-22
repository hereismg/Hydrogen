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
#include <List.h>
#include <Integer.h>

using namespace std;
using namespace hdg;

TEST(Smoke, Equation_1) {
    sInteger int1 = make_shared<Integer>(1);
    sObject  int2 = make_shared<Integer>(1);

    auto res = int1->equation(int2);
    ASSERT_TRUE(res->isTrue());
}

TEST(Smoke, Equation_2) {
    sInteger int1 = make_shared<Integer>(1);
    sObject  int2 = make_shared<Integer>(2);

    auto res = int1->equation(int2);
    ASSERT_FALSE(res->isTrue());
}

TEST(Smoke, Clone_1){
    auto myList = std::make_shared<List>();
    myList->getList().emplace_back(make_shared<Integer>(1));
    myList->getList().emplace_back(make_shared<Integer>(2));
    myList->getList().emplace_back(make_shared<Integer>(3));

    auto listCopy = myList->clone();
    ASSERT_NE(listCopy, nullptr);
    ASSERT_EQ(typeid(*(listCopy.get())), typeid(List));
    List* listCopy_ptr = dynamic_cast<List*>(listCopy.get());
    ASSERT_EQ(myList->getList().size(), listCopy_ptr->getList().size());
    
    myList->getList()[0] = make_shared<Integer>(10);
    myList->getList()[1] = make_shared<Integer>(10);
    myList->getList()[2] = make_shared<Integer>(10);

    ASSERT_TRUE(myList->equation(listCopy)->isTrue());
}
