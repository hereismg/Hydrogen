#include <memory>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <kernel/Lexer.h>
#include <kernel/Parser.h> 
#include <node/ObjectNode.h>
#include <node/expr.h>
#include <node/stmt_node.h>
#include <object/List.h>
#include <object/Integer.h>
#include <object/Object.h>
#include <object/state_machine.h>

using namespace std;
using namespace hdg;

TEST(String, getType_uniqueness){
    wVarType strType = String::getType();

    auto num = std::make_shared<Integer>(20250609);
    strType.lock()->refEnvir().setSymbol("len", num);

    wVarType strType2 = String::getType();

    auto obj = strType2.lock()->refEnvir().getSymbol("len");

    ASSERT_TRUE(obj->equation(num)->isTrue());
}

TEST(List, getType_uniqueness){
    wVarType strType = List::getType();

    auto num = std::make_shared<Integer>(20250609);
    strType.lock()->refEnvir().setSymbol("len", num);

    wVarType strType2 = String::getType();

    auto obj = strType2.lock()->refEnvir().getSymbol("len");

    ASSERT_TRUE(obj->equation(num)->isTrue());
}

TEST(List, from_1) {
    sObject obj = Integer::from(1);

    auto opt = List::from(obj);

    ASSERT_FALSE(opt.has_value());
}

TEST(List, from_2) {
    sObject obj = std::make_shared<List>();

    auto opt = List::from(obj);

    ASSERT_TRUE(opt.has_value());
}


TEST(Integer, from_1) {
    sObject obj = Integer::True;

    auto num = Integer::from(1);

    ASSERT_TRUE(obj->equation(num)->isTrue());
}

TEST(NodeJSON, _1){
    auto expr = BinOperNode::createPlus(5, 2);
    ASSERT_NE(expr, nullptr);

    cout << expr->toJSON().dump(4) << endl;
}

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

    auto listCopy = List::from(myList->clone()).value();

    ASSERT_EQ(myList->getList().size(), listCopy->getList().size());
    
    myList->getList()[0] = make_shared<Integer>(10);
    myList->getList()[1] = make_shared<Integer>(10);
    myList->getList()[2] = make_shared<Integer>(10);

    ASSERT_FALSE(myList->equation(listCopy)->isTrue());
}

TEST(Smoke, Clone_2){
    size_t count = 5;
    auto myList = std::make_shared<List>(count, nullptr);
    for (int i = 0; i < count; i++) {
        myList->getList()[i] = make_shared<Integer>(i);
    }

    auto arr2di = std::make_shared<List>(count, nullptr);
    for (int i = 0; i < count; i++) {
        arr2di->getList()[i] = myList->clone();
    }

    for (int i = 0; i < count; i++) {
        // arr2di->getList()
    }
    // myList->getList()[0]

    // for (int )
}

TEST(Smoke, getClass_1) {
    auto obj1 = std::make_shared<Integer>(1);
    ASSERT_EQ(obj1->getClass(), "Integer");

    auto obj2 = std::make_shared<List>();
    ASSERT_EQ(obj2->getClass(), "List");

    auto obj3 = std::make_shared<String>();
    ASSERT_EQ(obj3->getClass(), "String");
}


TEST(Smoke, list_1) {
    auto list = std::make_shared<List>();
    list->getList().emplace_back(std::make_shared<Integer>(1));
    list->getList().emplace_back(std::make_shared<Integer>(2));
    list->getList().emplace_back(std::make_shared<Integer>(3));

    InterpreterVisitor visitor;

    auto obj = list->brackets({ std::make_shared<Integer>(1) }, visitor);
    ASSERT_TRUE(obj->equation(std::make_shared<Integer>(2))->isTrue());
}


/**********************************************
 * String
 **********************************************/

TEST(String, equation_1) {
    auto str1 = std::make_shared<String>("1");
    auto str2 = std::make_shared<String>("1");

    ASSERT_TRUE(str1->equation(str2)->isTrue());
}

TEST(String, equation_2) {
    auto str1 = std::make_shared<String>("");
    auto str2 = std::make_shared<String>("");

    ASSERT_TRUE(str1->equation(str2)->isTrue());
}

TEST(String, plus_1) {
    auto str1 = std::make_shared<String>("1");
    auto str2 = std::make_shared<String>("2");

    auto actual = str1->plus(str2);

    auto expected = std::make_shared<String>("12");

    ASSERT_TRUE(actual->equation(expected)->isTrue());
}

TEST(String, plus_2) {
    auto str1 = std::make_shared<String>("");
    auto str2 = std::make_shared<String>("");

    auto actual = str1->plus(str2);

    auto expected = std::make_shared<String>("");

    ASSERT_TRUE(actual->equation(expected)->isTrue());
}

TEST(String, div_1) {
    auto str = std::make_shared<String>("12 34 56");
    auto split = std::make_shared<String>(" ");

    auto actual_list = str->div(split);

    ASSERT_NE(actual_list, nullptr);

    auto expected_list = List::from({
        "12",
        "34",
        "56"
    });

    ASSERT_TRUE(actual_list->equation(expected_list)->isTrue());
}

TEST(String, div_2) {
    auto str = std::make_shared<String>("12");
    auto split = std::make_shared<String>(" ");

    auto actual_list = str->div(split);

    ASSERT_NE(actual_list, nullptr);

    auto expected_list = String::buildStrList({
        "12"
    });

    ASSERT_TRUE(actual_list->equation(expected_list)->isTrue());
}

TEST(String, div_3) {
    auto str = std::make_shared<String>("1");
    auto split = std::make_shared<String>("1");

    auto actual_list = str->div(split);

    ASSERT_NE(actual_list, nullptr);

    auto expected_list = String::buildStrList({});

    ASSERT_TRUE(actual_list->equation(expected_list)->isTrue());
}



/**********************************************
 * StateMachine
 **********************************************/

/**
 * sm Test{
 *     1 + 2
 * }
 */

TEST(SM, exe_1){
    vector<uNode> stmts;
    stmts.emplace_back(BinOperNode::createPlus(1, 2));
    auto sm = StateMachine::create(std::move(stmts));

    InterpreterVisitor visitor;

    sm->exe(visitor, 0);

    auto res = Integer::from(visitor.getResult());
    ASSERT_TRUE(res->equation(Integer::from(3))->isTrue());
}

/**
 * sm Test{
 *     var a = 1 + 2
 *     a + 3
 * }
 * Test[0:2]()
*/
TEST(SM, exe_2){
    vector<uNode> stmts;
    stmts.emplace_back(DefNode::create("a", BinOperNode::createPlus(1, 2)));
    stmts.emplace_back(BinOperNode::createPlus(IdentNode::create("a"), IntNode::create(3)));
    auto sm = StateMachine::create(std::move(stmts));

    InterpreterVisitor visitor;

    sm->exe(visitor, 0, 2);

    auto res = Integer::from(visitor.getResult());
    ASSERT_TRUE(res->equation(Integer::from(6))->isTrue());
}

/**
 * sm Test{
 *     var a = 1 + 2
 *     a + 3
 * }
*/
