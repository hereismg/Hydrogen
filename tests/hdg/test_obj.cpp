#include <memory>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <kernel/Lexer.h>
#include <kernel/Parser.h> 
#include <node/ObjectNode.h>
#include <node/BinaryOperatorNode.h>
#include <object/List.h>
#include <object/Integer.h>

using namespace std;
using namespace hdg;

TEST(VarType, _1){
    
}

TEST(NodeJSON, _1){
    uNode left = std::make_unique<IntNode>(5);
    uNode right = std::make_unique<IntNode>(2);

    Token plus(Token::Type::PLUS);

    auto expr = std::make_unique<BinOperNode>(
        std::move(plus),
        std::move(left),
        std::move(right)
    );

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

    auto listCopy = myList->clone();
    ASSERT_NE(listCopy, nullptr);
    ASSERT_EQ(typeid(*(listCopy.get())), typeid(List));
    List* listCopy_ptr = dynamic_cast<List*>(listCopy.get());
    ASSERT_EQ(myList->getList().size(), listCopy_ptr->getList().size());
    
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

TEST(String, equation_1){
    auto str1 = std::make_shared<String>("1");
    auto str2 = std::make_shared<String>("1");

    ASSERT_TRUE(str1->equation(str2)->isTrue());
}

TEST(String, equation_2){
    auto str1 = std::make_shared<String>("");
    auto str2 = std::make_shared<String>("");

    ASSERT_TRUE(str1->equation(str2)->isTrue());
}

TEST(String, plus_1){
    auto str1 = std::make_shared<String>("1");
    auto str2 = std::make_shared<String>("2");

    auto actual = str1->plus(str2);

    auto expected = std::make_shared<String>("12");

    ASSERT_TRUE(actual->equation(expected)->isTrue());
}

TEST(String, plus_2){
    auto str1 = std::make_shared<String>("");
    auto str2 = std::make_shared<String>("");

    auto actual = str1->plus(str2);

    auto expected = std::make_shared<String>("");

    ASSERT_TRUE(actual->equation(expected)->isTrue());
}

TEST(String, div_1)
{
    auto str = std::make_shared<String>("12 34 56");
    auto split = std::make_shared<String>(" ");

    auto actual_list = str->div(split);

    ASSERT_NE(actual_list, nullptr);

    auto expected_list = String::buildStrList({
        "12",
        "34",
        "56"
    });

    ASSERT_TRUE(actual_list->equation(expected_list)->isTrue());
}

TEST(String, div_2)
{
    auto str = std::make_shared<String>("12");
    auto split = std::make_shared<String>(" ");

    auto actual_list = str->div(split);

    ASSERT_NE(actual_list, nullptr);

    auto expected_list = String::buildStrList({
        "12"
    });

    ASSERT_TRUE(actual_list->equation(expected_list)->isTrue());
}

TEST(String, div_3)
{
    auto str = std::make_shared<String>("1");
    auto split = std::make_shared<String>("1");

    auto actual_list = str->div(split);

    ASSERT_NE(actual_list, nullptr);

    auto expected_list = String::buildStrList({});

    ASSERT_TRUE(actual_list->equation(expected_list)->isTrue());
}