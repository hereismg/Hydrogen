// #ifndef HDG_NEWPARSER_H
// #define HDG_NEWPARSER_H

// #include <set>
// #include <memory>

// #include "NewLexer.h"
// #include "../basic/Environment.h"
// #include "../node/Node.h"

// using namespace hdg;

// namespace hdg_lexer{
//     class Parser {
//         public:
//             std::unique_ptr<Node> run(const std::vector<Token>& tokens, std::weak_ptr<Environment> envir);
    
//         protected:
//             size_t ptr = 0;
//             void advance();
//             void retreat();

//             // 执行单元
//             std::unique_ptr<Node> ExeUnit   (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> LoopUnit  (std::weak_ptr<Environment> envir);

//             // 语句
//             std::unique_ptr<Node> Stmt      (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> LoopStmt  (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> IfStmt    (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> WhileStmt (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> AssignStmt(std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> Array     (std::weak_ptr<Environment> envir);

//             // 定义
//             std::unique_ptr<Node> Def       (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> FuncDef   (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> Params    (std::weak_ptr<Environment> envir);

//             // 表达式
//             std::unique_ptr<Node> Expr      (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> LogicExpr (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> CompExpr  (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> ArithExpr (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> Term      (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> Factor    (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> Power     (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> Primary   (std::weak_ptr<Environment> envir);
//             std::unique_ptr<Node> Call      (std::weak_ptr<Environment> envir);

//             std::unique_ptr<Node> binOper(
//                 Environment* environment,
//                 const std::set<Token, std::less<>>&opers,
//                 std::function<Node*(Environment* envir)> funA,
//                 std::function<Node*(Environment* envir)> funB=nullptr
//             );
//             std::shared_ptr<Node> unaryOper(
//                 Environment* environment,
//                 const std::set<Token, std::less<>>&opers,
//                 std::function<Node*(Environment* envir)> fun
//             );
//         };
// }

// #endif