#ifndef HDG_NEWPARSER_H
#define HDG_NEWPARSER_H

#include <set>
#include <memory>

#include "NewLexer.h"
#include "../basic/Environment.h"
#include "../node/Node.h"

namespace hdg_lexer{
    
    class Parser {
    public:
        std::unique_ptr<hdg::Node> run(const std::vector<Token>& tokens, std::weak_ptr<hdg::Environment> envir);

    protected:
        size_t ptr = 0;
        void advance();
        void retreat();

        // 执行单元
        std::unique_ptr<hdg::Node> ExeUnit   (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> LoopUnit  (std::weak_ptr<hdg::Environment> envir);

        // 语句
        std::unique_ptr<hdg::Node> Stmt      (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> LoopStmt  (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> IfStmt    (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> WhileStmt (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> AssignStmt(std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> Array     (std::weak_ptr<hdg::Environment> envir);

        // 定义
        std::unique_ptr<hdg::Node> Def       (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> FuncDef   (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> Params    (std::weak_ptr<hdg::Environment> envir);

        // 表达式
        std::unique_ptr<hdg::Node> Expr      (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> LogicExpr (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> CompExpr  (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> ArithExpr (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> Term      (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> Factor    (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> Power     (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> Primary   (std::weak_ptr<hdg::Environment> envir);
        std::unique_ptr<hdg::Node> Call      (std::weak_ptr<hdg::Environment> envir);

        std::unique_ptr<hdg::Node> binOper(
            hdg::Environment* envir,
            const std::set<Token, std::less<>>&opers,
            std::function<hdg::Node*(hdg::Environment* envir)> funA,
            std::function<hdg::Node*(hdg::Environment* envir)> funB=nullptr
        );
        std::shared_ptr<hdg::Node> unaryOper(
            hdg::Environment* envir,
            const std::set<Token, std::less<>>&opers,
            std::function<hdg::Node*(hdg::Environment* envir)> fun
        );
    };
}

#endif