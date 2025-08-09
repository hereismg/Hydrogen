#include <memory>
#include <fstream>
#include <chrono>

#include <gtest/gtest.h>
#include <sml.hpp>

#include <kernel/Lexer.h>
#include <kernel/Parser.h> 
#include <basic/Environment.h>
#include <node/ObjectNode.h>
#include <node/expr.h>
#include <node/stmt_node.h>
#include <node/unit_node.h>
#include <object/Integer.h>
#include <object/state_machine.h>

using namespace std;
using namespace hdg;

typedef enum {
    Expr,
    IfStmt,
    ExeUnit,
    VarDef
} ParserType;
class Interepreter_TEST_P: public testing::TestWithParam<tuple<
    string,         // 标识符
    string,         // 代码
    sObject,        // 预期结果
    ParserType      // 执行函数
>>{};

// std::string debug_json_dump(const nlohmann::json& j) {
//     return j.dump(4);  // 实际调用内联函数
// }

void debug_append_json_dump(
    const nlohmann::json& j,
    const std::string& context = "",
    const std::string& filename = "debug_json.log"
) {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    
    std::ofstream outfile;
    outfile.open(filename, std::ios_base::app);
    
    if (outfile.is_open()) {
        // 写入时间戳
        outfile << "[" << std::put_time(std::localtime(&now_time), "%F %T") << "] ";
        
        // 写入上下文信息
        if (!context.empty()) {
            outfile << context << " ";
        }
        cout << j.dump(2) << endl;
        
        // 写入JSON内容
        outfile << j.dump(2) << "\n\n";
        outfile.close();
    }
}

TEST_P(Interepreter_TEST_P, _){
    auto [id, code, expected, parserType] = GetParam();
    // cout << id << endl;
    string path = "<stdin>";
    Lexer lexer;

    std::vector<Token> tokens = lexer.run(path, &code);

    Environment envir2; // mgtodo: 这将来要弃用

    Parser parser(tokens, &envir2);

    uNode root;
    switch (parserType) {
    case ParserType::Expr : 
        root = parser.expr();
        break;
    case ParserType::IfStmt :
        root = parser.ifStmt();
        break;
    case ParserType::ExeUnit :
        root = parser.exeUnit();
        break;
    case ParserType::VarDef :
        root = parser.varDef();
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

    if (!obj->equation(expected)->isTrue()){
        cout << obj->toString() << endl;
        cout << expected->toString() << endl;
        ASSERT_TRUE(false);
    }
}



/**********************************************
 * Test 1. Parse Basic Type
 **********************************************/

INSTANTIATE_TEST_SUITE_P(ParseBasicType_String, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"ParseBasicType_String",
R"({
    var a = "123"
    a
})",
make_shared<String>("123"),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"ParseBasicType_String",
R"({
    var a = "12 34 56"
    var split = " "
    var list = a / split
    list
})",
List::from({
    "12",
    "34",
    "56"
}),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"ParseBasicType_String",
R"({
    var a = "12 34 56" / " "
    a
})",
List::from({
    "12",
    "34",
    "56"
}),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{ 
"ParseBasicType_String",
R"({
    var a = "12 34 56 "
    var list = a / " "
    list
})",
List::from({
    "12",
    "34",
    "56" // mgtodo 思考：这里不用再加一个空字符串吗？
}),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{ 
"ParseBasicType_String",
R"({
    var a = "12" + "34" + "56"
    a
})",
std::make_shared<String>("123456"),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"ParseBasicType_String",
R"({
    var list = ["Hello World!"]
    list
})",
String::buildStrList({
    "Hello World!"
}),
ParserType::ExeUnit
}
));

/**********************************************
 * Test 1. Expr
 **********************************************/

INSTANTIATE_TEST_SUITE_P(Expr_Arithmetic, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"0",
"1 + 2",
make_shared<Integer>(3),
ParserType::Expr
},

tuple<string, string, sObject, ParserType>{
"1",
"1 + ( 2 + 3 ) * 4",
make_shared<Integer>(21),
ParserType::Expr
},

tuple<string, string, sObject, ParserType>{
"2",
"0 - 1",
make_shared<Integer>(-1),
ParserType::Expr
},

tuple<string, string, sObject, ParserType>{
"2",
"8 / (2 + 1) * 3",
make_shared<Integer>(6),
ParserType::Expr
}
));

INSTANTIATE_TEST_SUITE_P(Expr_CompExpr, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"0",
"1 > 2",
Integer::False,
ParserType::Expr
},

tuple<string, string, sObject, ParserType>{
"0",
"1 < 2",
Integer::True,
ParserType::Expr
},

tuple<string, string, sObject, ParserType>{
"0",
"1 >= 2",
Integer::False,
ParserType::Expr
},

tuple<string, string, sObject, ParserType>{
"0",
"1 <= 2",
Integer::True,
ParserType::Expr
},


tuple<string, string, sObject, ParserType>{
"0",
"2 >= 2",
Integer::True,
ParserType::Expr
}
));

/**********************************************
 * Test 3. Variable Def
 **********************************************/

INSTANTIATE_TEST_SUITE_P(VariableDef, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"1234",
R"({
var a = 1
a
})",
make_shared<Integer>(1),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"3",
"{var a = 1 var b = 2 a + b}",
make_shared<Integer>(3),
ParserType::ExeUnit
},

//tuple<string, string, sObject, ParserType>{
//"VariableDef_3",
//R"({
//    var grid = [1, 2, 3]
//    grid
//})",
//std::make_shared<List>(std::move(vector<int64_t>({1, 2, 3}))),
//ParserType::ExeUnit
//},

tuple<string, string, sObject, ParserType>{
"VariableDef_3",
R"({
    var grid = [
    ["1", "2", "3"],
    ["4", "5", "6"],
    ["7", "8", "9"]
    ]
    grid[1][1]
})",
make_shared<String>("5"),
ParserType::ExeUnit
}
));


/**********************************************
 * Test 4. LVal and RVal
 **********************************************/


INSTANTIATE_TEST_SUITE_P(LValAndRVal, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"LValAndRVal_0",
R"({
    var list = [1, 2]
    list[0] = 3
    list[0]
})",
make_shared<Integer>(3),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801",
R"({
    var list = [[1, 2], 3]
    list[0][0]
})",
make_shared<Integer>(1), 
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801", 
R"({
    var list = [1, 2025]
    list[0] = list
    list[0][0][0][0][0][0][0][0][0][0][1]
})",
make_shared<Integer>(2025), // mgtodo: 是否会造成内存泄漏？
ParserType::ExeUnit
}
));

INSTANTIATE_TEST_SUITE_P(LRValAndFunction, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"52801",
R"({
    var list = [1, 2, 3]
    function getList(){
        list
    }
    getList()[1] = 2025
    list[1]
})",
make_shared<Integer>(2025), 
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801",
R"({
    function add(a, b){
        a + b
    }
    function mine(a, b){
        a - b
    }
    var list = [add, mine]
    list[0](1, 2)
})",
make_shared<Integer>(3), 
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801",
R"({
    function add(pair){
        pair[0] + pair[1]
    }
    add([1, 2])
})",
make_shared<Integer>(3), 
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801",
R"({
    function oper(){
        function add(a, b){
            a + b
        }
        add
    }
    
    oper()(1, 2)
})",
make_shared<Integer>(3), 
ParserType::ExeUnit
}

));


/**********************************************
 * Test 5. Process Control
 **********************************************/

INSTANTIATE_TEST_SUITE_P(ProcessControl_IfStmt, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"ProcessControl_IfStmt_0",
R"(
if 1 + 1 {
    10
} else {
    5
}
)",
make_shared<Integer>(10),
ParserType::IfStmt
},

tuple<string, string, sObject, ParserType>{
"1",
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
make_shared<Integer>(10),
ParserType::IfStmt
},

tuple<string, string, sObject, ParserType>{
"2",
R"({
var a = 1
if a {
    a
}
else {
    a - 1
}
})",
make_shared<Integer>(1),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"0527",
R"({
var a = 1
if a {
    var b = 1
    if b >= 2 {
        1111
    }
    elif b <= 1 {
        2222
    }
    else {
        3333
    }
}
else {
    a - 1
}
})",
make_shared<Integer>(2222),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"0527",
R"({
var a = 1
if a != 1{
    2025
}
else {
    2024
}
})",
make_shared<Integer>(2024),
ParserType::ExeUnit
}
));


INSTANTIATE_TEST_SUITE_P(ProcessControl_WhileStmt, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"ProcessControl_WhileStmt_0",
R"({
var sum = 0
var counter = 5
while counter {
    sum = sum + counter
    counter = counter - 1
}
sum
})",
make_shared<Integer>(15),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"ProcessControl_WhileStmt_0",
R"({
var sum = 0
var counter = 5
while counter > 0 {
    sum = sum + counter
    counter = counter - 1
}
sum
})",
make_shared<Integer>(15),
ParserType::ExeUnit
}
));

/**********************************************
 * Test 6. Function
 **********************************************/

INSTANTIATE_TEST_SUITE_P(Function, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"111",
R"({
    function add(a, b){
        a + b
    }
    add(1, 2)
})",
make_shared<Integer>(3),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"2",
R"({
function fun() {
    10
}
fun()
})",
make_shared<Integer>(10),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"2",
R"({
    function getNum(sum){
        sum
    }
    var sum = 5
    sum = sum + getNum(sum)
    sum
})",
make_shared<Integer>(10),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801",
R"({
    var sum = 0
    function fun(a) {
        if a {
            sum = sum + fun(a - 1)
        }
        a
    }
    fun(2)
    sum
})",
make_shared<Integer>(1),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801",
R"({
function Animal(oper){
    var age = 180
    var phone = 123456789

    oper()
}

function getAge(){
    age
}

function getPhone(){
    phone
}

Animal(getAge)
})",
make_shared<Integer>(180),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"52801",
R"({
function fun(l, r) {
    if l < r {
        var mid = (l + r) / 2
        fun(l, mid)
        fun(mid + 1, r)
        var i = l
        var j = mid + 1
        var k = 0
        while (mid - i + 1) * (r - j + 1) {
            if nums[i] < nums[j] {
                temp[k] = nums[i]
                k = k + 1
                i = i + 1
            } else {
                temp[k] = nums[j]
                k = k + 1
                j = j + 1
            }
        }
        while mid - i + 1 {
            temp[k] = nums[i]
            k = k + 1
            i = i + 1
        }
        while r - j + 1 {
            temp[k] = nums[j]
            k = k + 1
            j = j + 1
        }
        k = 0
        while l <= r {
            nums[l] = temp[k]
            l = l + 1
            k = k + 1
        }
    }
}

var n = 10
var nums = [1, 5, 3, 9, 2, 3, 1, 9, 5, 2]
var temp = nums.clone()
fun(0, n - 1)
nums
})",
List::from({1, 1, 2, 2, 3, 3, 5, 5, 9, 9}),
ParserType::ExeUnit
}


));


/**********************************************
 * Test 7. Postfix
 **********************************************/

INSTANTIATE_TEST_SUITE_P(Postfix_Dot, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"Postfix_Dot",
R"({
    var list = [1, 2]
    list.append(3)
})",
List::from({1, 2, 3}),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"Postfix_Dot",
R"({
    var list = [9, 6, 5, 8, 3, 7]
    list.append(list.head()).append(list.tail())
})",
List::from({9, 6, 5, 8, 3, 7, 9, 9}),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"Postfix_Dot",
R"({
    var list = [9, 6, 5, 8, 3, 7]
    list.length()
})",
Integer::from(6),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"Postfix_Dot",
R"({
    var list = [9, 6, 5, 3]
    list.extend(list)
})",
List::from({9, 6, 5, 3, 9, 6, 5, 3}),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"Postfix_Dot",
R"({
    var list = [9, 6, 5, 3]
    list.reverse()
})",
List::from({3, 5, 6, 9}),
ParserType::ExeUnit
},

tuple<string, string, sObject, ParserType>{
"Postfix_Dot",
R"({
    var cl1 = [1, 9]
    var cl2 = cl1.clone()
    var ncl1 = [2, 8]
    var ncl2 = ncl1
    cl1[0] = 0
    cl2[1] = 0
    ncl1[0] = 0
    ncl2[1] = 0
    var res = []
    res.extend(cl1)
    res.extend(cl2)
    res.extend(ncl1)
    res.extend(ncl2)
    res
})",
List::from({0, 9, 1, 0, 0, 0, 0, 0}),
ParserType::ExeUnit
}

// tuple<string, string, sObject, ParserType>{
// "Postfix_Dot",
// R"({
// function solution(layer, a, b, c, result){
//     if layer != 1{
//         result = result + a + "->" + b + "\n"
//         solution(layer-1, a, c, b, result)
//         result = result + b "->" + c + "\n"
//     }
//     result
// }

// var result = ""
// solution(2, "x", "y", "z", result)
// })",
// String::from("12"),
// ParserType::ExeUnit
// }

));