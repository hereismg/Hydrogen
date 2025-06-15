//
// Created by Magnesium on 2023/7/16.
//

#include "../../include/kernel/Parser.h"

#include <set>
#include <cassert>

#include "../../include/node/CallNode.h"
#include "../../include/node/StatementsNode.h"
#include "../../include/node/ObjAssignNode.h"
#include "../../include/node/UnaryOperatorNode.h"
#include "../../include/node/ObjAccessNode.h"
#include "../../include/node/IfNode.h"
#include "../../include/node/ForNode.h"
#include "../../include/node/WhileNode.h"
#include "../../include/node/BinaryOperatorNode.h"
#include "../../include/node/stmt_node.h"
#include "../../include/node/unit_node.h"
#include "../../include/node/ObjectNode.h"

namespace hdg {
    Parser::Parser(std::vector<Token> tokens, Environment* environment):
            m_tokens(move(tokens)), m_currentToken(m_tokens.begin()), m_environment(environment){
    }

    void Parser::advance() {
        if (m_currentToken->getType() != Token::EF) m_currentToken++;
    }

    void Parser::advanceAndEL() {
        do {
            advance();
        } while(m_currentToken->getType() == Token::EL);
    }

    void Parser::retreat() {
        if (m_currentToken != m_tokens.begin()) m_currentToken--;
    }

    uNode Parser::exeUnit(){
        while(m_currentToken->getType() == Token::EL) advance();
        if (m_currentToken->getType() != Token::LBRACE){
            throw -1;
        }
        advance();

        auto unit = std::make_unique<new_ExeUnitNode>();
        while(m_currentToken->getType() != Token::RBRACE){
            // end of file
            if (m_currentToken->getType() == Token::EL){
                advance();
                continue;
            }
            uNode stmt;

            auto resOpt = assignStmt();
            if (resOpt.has_value()){
                while (m_currentToken->getType() == Token::EL){
                    advance();
                }

                unit->getList().emplace_back(move(resOpt.value()));
                continue;
            }

            stmt = ifStmt();
            if (stmt != nullptr){
                while (m_currentToken->getType() == Token::EL){
                    advance();
                }

                unit->getList().emplace_back(move(stmt));
                continue;
            }

            stmt = whileStmt();
            if (stmt != nullptr){
                while (m_currentToken->getType() == Token::EL){
                    advance();
                }

                unit->getList().emplace_back(move(stmt));
                continue;
            }

            stmt = funcDef();
            if (stmt != nullptr){
                while (m_currentToken->getType() == Token::EL){
                    advance();
                }

                unit->getList().emplace_back(move(stmt));
                continue;
            }

            stmt = varDef();
            if (stmt != nullptr){
                while (m_currentToken->getType() == Token::EL){
                    advance();
                }

                unit->getList().emplace_back(move(stmt));
                continue;
            }

            stmt = expr();
            if (stmt != nullptr){
                while (m_currentToken->getType() == Token::EL){
                    advance();
                }

                unit->getList().emplace_back(move(stmt));
                continue;
            }
             
        }
        advance();
        
        return unit;
    }

    uNode Parser::ifStmt(){
        auto ifStmtNode = std::make_unique<new_IfStmtNode>();

        // 'if' Expr ExeUnit
        ignoreEL();
        if (!m_currentToken->match(Token::KEYWORD, "if")) return nullptr;

        Position *pos = ifStmtNode->thisPosition();
        pos->setStart(m_currentToken->thisPosition()->getStart());
        advanceAndEL();

        auto cond = expr();
        auto exe = exeUnit();
        ifStmtNode->addBranch(move(cond), move(exe));


        // { 'elif' Expr ExeUnit }
        ignoreEL();
        while(m_currentToken->match(Token::Token::KEYWORD, "elif")){
            advance();
            ignoreEL();
            cond = expr();
            exe = exeUnit();
            ifStmtNode->addBranch(move(cond), move(exe));
        }

        // ['else' ExeUnit ]
        ignoreEL();
        if (m_currentToken->match(Token::KEYWORD, "else")){
            advanceAndEL();
            exe = exeUnit();
            ifStmtNode->addElseBranch(move(exe));
        }

        pos->setEnd(m_currentToken->thisPosition()->getEnd());
        return ifStmtNode;
    }

    uNode Parser::whileStmt(){
        if (!m_currentToken->match(Token::KEYWORD, "while")) return nullptr;

        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());
        advance();

        uNode cond = expr();

        uNode loopUnit = exeUnit(); // hdgtodo: 后面应该支持 break
    
        pos.setEnd(m_currentToken->thisPosition()->getEnd());
        return std::make_unique<new_WhileStmtNode>(
            move(cond), 
            move(loopUnit)
        );
    }

    optional<uNode> Parser::assignStmt(){
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());

        auto start = m_currentToken;

        // 1. lVal
        auto resOpt = new_PostfixExpr();
        if (!resOpt.has_value()) return std::nullopt;
        uNode lVal = move(resOpt.value());

        // 2. '='
        if (m_currentToken->getType() != Token::EQ){
            // retreat();
            m_currentToken = start;
            return std::nullopt;
        }
        advance();
        
        // 3. rVal
        uNode rVal = expr();

        // 4 return
        pos.setEnd(m_currentToken->thisPosition()->getEnd());
        return std::make_unique<new_AssignNode>(move(lVal), move(rVal), pos);
    }

    // uNode Parser::new_ValBuild() {
    //     return nullptr;
    // }

    uNode Parser::varDef() {
        while (m_currentToken->getType() == Token::EL) advance();
        
        // 1. 关键字 'var'
        if (!m_currentToken->match(Token::KEYWORD, "var")) return nullptr;
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());
        advance();

        // 2. 标识符 IDENT
        if (m_currentToken->getType() != Token::IDENT) {
            assert(false); // 应该抛出异常
        }
        std::string ident = m_currentToken->getValue();
        advance();

        // 3. 等于号 '='
        if (m_currentToken->getType() != Token::EQ) {
            assert(false);
        }
        advance();

        // 4. 表达式
        uNode node = expr();

        pos.setEnd(m_currentToken->thisPosition()->getEnd());

        return std::make_unique<DefNode>(ident, move(node), pos);
    }

    // FuncDef    : 'func' IDENT  '(' Params ')'  ExeUnit
    uNode Parser::funcDef(){ // hdgtodo: AST 的基本设计原则是：尽力保留原始的代码信息
        while (m_currentToken->getType() == Token::EL) advance();

        // 1. 关键字 'function'
        if (!m_currentToken->match(Token::KEYWORD, "function")){
            return nullptr;
        }
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());
        advance();

        // 2. 标识符 IDENT
        if (m_currentToken->getType() != Token::IDENT) {
            assert(false); // 应该抛出异常
        }
        std::string ident = m_currentToken->getValue();
        advance();

        // 3. 参数 '(' Params ')'
        if (m_currentToken->getType() != Token::LPAREN){
            assert(false); // 应该抛出异常
        }
        advance();

        auto params = new_Params();

        if (m_currentToken->getType() != Token::RPAREN){
            assert(false); // 应该抛出异常
        }
        advance();

        // 4. 函数的执行体 ExeUnit
        auto unit = exeUnit();

        // 5. 构建结点
        pos.setEnd(m_currentToken->thisPosition()->getEnd());
        
        uNode funNode = std::make_unique<New_FuncObjNode>(move(params), move(unit), pos);

        return std::make_unique<DefNode>(ident, move(funNode), pos);
    }

    uNode Parser::expr(){
        uNode expr;

        expr = listExpr();
        if (expr != nullptr) {
            return expr;
        }

        expr = new_CompExpr();
        if (expr != nullptr) {
            return expr;
        }

        assert(false);
        return nullptr;
    }

    uNode Parser::listExpr(){
        while (m_currentToken->getType() == Token::EL) advance();
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());

        // 1. 左方括号 '['
        if (m_currentToken->getType() != Token::LBRACKET) return nullptr;
        advance();
        while (m_currentToken->getType() == Token::EL) advance();

        // 2. ExprArray
        std::vector<uNode> arr;
        if (m_currentToken->getType() != Token::RBRACKET){
            arr = new_ExprArray();
        }

        // 3. 右方括号 ']'
        ignoreEL();
        if (m_currentToken->getType() != Token::RBRACKET) {
            assert(false);
        }
        advance();

        pos.setEnd(m_currentToken->thisPosition()->getEnd());

        return std::make_unique<ListObjNode>(move(arr), pos);
    }

     uNode Parser::new_CompExpr(){
         Position pos;
         pos.setStart(m_currentToken->thisPosition()->getStart());

         uNode left = new_ArithExpr();

         Token oper = m_currentToken->getType();
         while( oper.getType() == Token::NE  ||
                oper.getType() == Token::EE  ||
                oper.getType() == Token::GT  ||
                oper.getType() == Token::LT  ||
                oper.getType() == Token::GTE ||
                oper.getType() == Token::LTE)
         {
             advance();

             uNode right = new_ArithExpr();
             assert(right != nullptr);

             pos.setEnd(m_currentToken->thisPosition()->getEnd());

             left = std::make_unique<BinOperNode>(
                     oper,
                     move(left),
                     move(right),
                     pos
             );
             oper = m_currentToken->getType();
         }

         return left;
     }

    uNode Parser::new_ArithExpr() {
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());

        uNode left = new_Term();

        while (m_currentToken->getType() == Token::PLUS || 
               m_currentToken->getType() == Token::MINUS) 
        {
            Token oper = m_currentToken->getType();
            advance();

            uNode right = new_Term();
            assert(right != nullptr);

            pos.setEnd(m_currentToken->thisPosition()->getEnd());

            left = std::make_unique<BinOperNode>(
                oper, 
                move(left),
                move(right),
                pos
            );
        }

        return left;
    }

    std::vector<std::string> Parser::new_Params(){
        std::vector<std::string> params;

        while(true) {
            if (m_currentToken->getType() == Token::EL){
                advance();
                continue;
            }

            if (m_currentToken->getType() != Token::IDENT) break;
            
            params.emplace_back(m_currentToken->getValue());
            advance();

            if (m_currentToken->getType() == Token::COMMA){
                advance();
                continue;
            }
            else{
                break;
            }
        }

        return params;
    }

    uNode Parser::new_Term() {
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());

        uNode left = new_Factor();
        assert(left != nullptr);

        while (m_currentToken->getType() == Token::MUL || 
               m_currentToken->getType() == Token::DIV) 
        {
            Token oper = m_currentToken->getType();
            advance();

            uNode right = new_Factor();

            pos.setEnd(m_currentToken->thisPosition()->getEnd());

            left = std::make_unique<BinOperNode>(
                oper, 
                move(left),
                move(right),
                pos
            );
        }

        return left;
    }

    uNode Parser::new_Factor() {
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());

        Token oper = m_currentToken->getType();
        switch(oper.getType()){
            case Token::PLUS: {
                auto resOpt = new_PostfixExpr();
                if (!resOpt.has_value()) assert(false);
                return move(resOpt.value()); // hdgtodo: 增加对单目运算符的支持
            }
            case Token::MINUS: {
                auto resOpt = new_PostfixExpr();
                if (!resOpt.has_value()) assert(false);
                return move(resOpt.value()); // hdgtodo: 增加对单目运算符的支持
            }
            default: {
                auto resOpt = new_PostfixExpr();
                if (!resOpt.has_value()) assert(false);
                return move(resOpt.value()); // hdgtodo: 增加对单目运算符的支持
            }
        }
    }

    optional<uNode> Parser::new_PostfixExpr() {
        Position pos;
        pos.setStart(m_currentToken->thisPosition()->getStart());

        auto resOpt = new_Primary();
        if (!resOpt.has_value()) return std::nullopt;
        uNode primary = move(resOpt.value());

        bool flag = true;
        while(flag){
            switch (m_currentToken->getType()){
            case Token::LPAREN : { // 圆括号 ()
                advance();

                std::vector<uNode> params;

                if (m_currentToken->getType() != Token::RPAREN){
                    params = new_ExprArray();                    
                }
                advance();

                pos.setEnd(m_currentToken->thisPosition()->getEnd());
                primary = PostfixNode::createParen(move(primary), move(params), pos);
                break;
            }
            case Token::LBRACKET : { // 方括号 []
                advance();

                std::vector<uNode> params;

                if (m_currentToken->getType() != Token::RBRACKET){
                    params = new_ExprArray();                    
                }
                advance();

                pos.setEnd(m_currentToken->thisPosition()->getEnd());
                primary = PostfixNode::createBracket(
                    move(primary),
                    move(params),
                    pos
                );
                break;
            }
            case Token::DOT : {  // 点号 .

            }
            default : {
                flag = false;
                break;
            }
            }
        }

        return primary;
    }


    optional<uNode> Parser::new_Primary() {
        uNode node;

        switch (m_currentToken->getType()){
            case Token::INT : {
                int64_t val = std::stoll(m_currentToken->getValue().c_str());
                auto pos = *m_currentToken->thisPosition();

                node = std::make_unique<IntNode>(val, pos);
                advance();
                return node;
            }
            case Token::IDENT : {
                std::string name = m_currentToken->getValue();
                advance();

                return std::make_unique<IdentNode>(name);
            }
            case Token::LPAREN : {
                auto pos = m_currentToken->thisPosition()->clone();
                advance();

                node = expr(); assert(node != nullptr);

                if (m_currentToken->getType() != Token::RPAREN) {
                    assert(false && "Throw Error! Expect ')'."); 
                }
                advance();
                return node;
            }
            case Token::STRING : {
                Position pos;
                pos.setStart(m_currentToken->thisPosition()->getStart());
                std::string val = m_currentToken->getValue();
                advance();

                pos.setEnd(m_currentToken->thisPosition()->getEnd());
                return std::make_unique<StrNode>(val, pos);
            }
            default:{
                 return std::nullopt;
            }
        }
    }

    std::vector<uNode> Parser::new_ExprArray() {
        std::vector<uNode> list;

        while(true) {
            uNode node = expr();

            assert(node != nullptr);

            list.emplace_back(move(node));

            if (m_currentToken->getType() == Token::COMMA) {
                advance();
                continue;
            }
            else{
                break;
            }
        }

        return list;
    }
} // hdg