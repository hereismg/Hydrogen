#include <memory>
#include <fstream>
#include <chrono>

#include <gtest/gtest.h>
#include <sml.hpp>

#include <kernel/Lexer.h>
#include <kernel/Parser.h> 
#include <basic/Environment.h>
#include <node/ObjectNode.h>
#include <node/BinaryOperatorNode.h>
#include <node/stmt_node.h>
#include <node/unit_node.h>

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
        root = parser.new_Expr();
        break;
    case ParserType::IfStmt :
        root = parser.new_IfStmt();
        break;
    case ParserType::ExeUnit :
        root = parser.new_ExeUnit();
        break;
    case ParserType::VarDef :
        root = parser.new_VarDef();
        break;
    default:
        ASSERT_TRUE(false);   
    }
    ASSERT_NE(root, nullptr);

    cout << root->toJSON().dump(4) << endl;

    InterpreterVisitor visitor;
    root->accept(visitor);

    // 检测正确性，未使用 equation 方法
    auto obj = visitor.getRVal().get();

    ASSERT_NE(obj, nullptr);

    obj->equation(expected);

    // ASSERT_EQ(typeid(*obj), typeid(Integer));

    // Integer* int_ptr = dynamic_cast<Integer*>(obj);

    // ASSERT_EQ(int_ptr->getValue(), expected);
}

INSTANTIATE_TEST_SUITE_P(ParseBasicType_String, Interepreter_TEST_P, testing::Values(
tuple<string, string, sObject, ParserType>{
"ParseBasicType_String",
R"({
    var txt = input()
    var arr = txt / " "
    print(arr)
    txt
})",
make_shared<String>("123"),
ParserType::ExeUnit
}
));