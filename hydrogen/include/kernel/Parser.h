//
// Created by Magnesium on 2023/7/16.
//

#pragma once

#include <functional>
#include <vector>
#include <optional>

#include "../basic/Token.h"
#include "../node/Node.h"

namespace hdg {
    using std::vector;
    using std::optional;
    using std::move;

    class Parser {
    protected:
        std::vector<Token> m_tokens;
        std::vector<Token>::iterator m_currentToken;
        Environment* m_environment;

    public:
        Parser(std::vector<Token> tokens, Environment* environment);

    public:
        void advance();
        void advanceAndEL();
        void ignoreEL() { while(m_currentToken->getType() == Token::Type::EL) advance(); }
        void retreat();

        uNode exeUnit();                   // ExeUnit       : '{' { IfStmt | AssignStmt | Expr } '}'
        uNode ifStmt();                    // IfStmt        : 'if' Expr ExeUnit 
                                           //                 {'elif' Expr ExeUnit }
                                           //                 ['else' ExeUnit ]
        uNode whileStmt();                 // WhileStmt     : 'while' Expr ExeUnit
        optional<uNode> assignStmt();      // AssignStmt    : PostfixExpr '=' Expr
        
        uNode varDef();                    // VarDef        : 'var'  IDENT '=' Expr | '[' [Params] ']'
        uNode funcDef();                   // FuncDef       : 'func' IDENT  '(' Params ')'  ExeUnit
        uNode stateDef();                  // StateDef      : 'sm'   IDENT ['(' Params ')'] ExeUnit
        
        uNode expr();                      // Expr          : LogicExpr
                                           //               | ListDefExpr
        uNode listExpr();                  // ListExpr      : '[' [Expr] ']'
        uNode logicExpr();                 // LogicExpr     : ('not' LogicExpr)
                                           //               | (CompExpr {('and' | 'or') CompExpr}) 
        uNode new_CompExpr();              // CompExpr      : ArithExpr {('>' | '<' | '>=' | ' <=' | '==' | '!=') ArithExpr}
        uNode new_ArithExpr();             // ArithExpr     : Term {('+' | '-') Term}
        uNode new_Term();                  // Term          : Factor {('*' | '/') Factor}
        uNode new_Factor();                // Factor        : {'+' | '-'} PostfixExpr
        optional<uNode> new_PostfixExpr(); // PostfixExpr   : Primary { PostfixSuffix }
                                           // PostfixSuffix : '(' ExprList ')'
                                           //               | '[' ExprList ']'
                                           //               | '.' IDENT '(' ExprList ')'
        optional<uNode> new_Primary();     // Primary       : INT_CONST
                                           //               | FLOAT_CONST
                                           //               | STR_CONST
                                           //               | IDENT
                                           //               | '(' ArithExpr ')'
        
        vector<std::string> new_Params();  // Params     : [ IDENT { ',' IDENT } ]
        vector<uNode> new_ExprArray();     // ExprList   : [ Expr  { ',' Expr  } ]
    };

} // hdg
