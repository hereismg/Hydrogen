// #ifndef HDG_NEWPARSER_H
// #define HDG_NEWPARSER_H

// #include <set>
// #include <memory>
// #include <functional>

// #include "NewLexer.h"
// #include "../basic/Environment.h"
// #include "../node/Node.h"
// #include "../node/BinaryOperatorNode.h"

// namespace hdg_lexer{
//     using wEnvir = std::weak_ptr<hdg::Environment>;
//     using uNode  = std::unique_ptr<hdg::Node>;

//     class Parser {
//     public:
//         Parser(const std::vector<Token>& tokens, wEnvir envir);
//         uNode run();

//     protected:
//         size_t m_ptr = 0;
//         std::vector<Token> m_tokens; // 也许可以用 std::span 优化

//         constexpr bool advance(){
//             if (m_ptr >= m_tokens.size()){
//                 return false;
//             }
//             else{
//                 ++ m_ptr;
//                 return true;
//             }
//         }
        
//         constexpr bool retreat(){
//             if (m_ptr <= 0) {
//                 return false;
//             }
//             else{
//                 -- m_ptr;
//                 return true;
//             }
//         }

//         // 执行单元
//         uNode ExeUnit   (wEnvir envir);
//         uNode LoopUnit  (wEnvir envir);

//         // 语句
//         uNode Stmt      (wEnvir envir);
//         uNode LoopStmt  (wEnvir envir);
//         uNode IfStmt    (wEnvir envir);
//         uNode WhileStmt (wEnvir envir);
//         uNode AssignStmt(wEnvir envir);
//         uNode Array     (wEnvir envir);

//         // 定义
//         uNode Def       (wEnvir envir);
//         uNode FuncDef   (wEnvir envir);
//         uNode Params    (wEnvir envir);

//         // 表达式
//         uNode Expr      (wEnvir envir);
//         uNode LogicExpr (wEnvir envir);
//         uNode CompExpr  (wEnvir envir);
//         uNode ArithExpr (wEnvir envir);
//         uNode Term      (wEnvir envir);
//         uNode Factor    (wEnvir envir);
//         uNode Power     (wEnvir envir);
//         uNode Primary   (wEnvir envir);
//         uNode Call      (wEnvir envir);

//         // 可复用函数
//         uNode binOper(
//             wEnvir envir,
//             const std::vector<Token>& opers,
//             std::function<uNode(wEnvir envir)> funA,
//             std::function<uNode(wEnvir envir)> funB=nullptr
//         );
//         uNode unaryOper(
//             wEnvir envir,
//             const std::vector<Token>& opers,
//             std::function<uNode(wEnvir envir)> fun
//         );
//     };
// }

// #endif