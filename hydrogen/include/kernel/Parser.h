//
// Created by Magnesium on 2023/7/16.
//


#ifndef HDG_PARSER_H
#define HDG_PARSER_H

#include <functional>
#include <vector>

#include "../basic/Token.h"
#include "../node/Node.h"

namespace hdg {

    class Parser {
    protected:
        std::vector<Token> m_tokens;
        std::vector<Token>::iterator m_currentToken;
        Environment* m_environment;

    public:
        Parser(std::vector<Token> tokens, Environment* environment);
        Node* run();

    public:
        void advance();
        void retreat();

        Node* expr      (Environment* environment);
        Node* compExpr  (Environment* environment);
        Node* arithExpr (Environment* environment);
        Node* term      (Environment* environment);
        Node* factor    (Environment* environment);
        Node* power     (Environment* environment);
        Node* call      (Environment* environment);
        Node* atom      (Environment* environment);
        Node* ifExpr    (Environment* environment);
        Node* forExpr   (Environment* environment);
        Node* whileExpr (Environment* environment);
        Node* funcExpr  (Environment* environment);
        Node* statements(Environment* environment);
        Node* core      (Environment* environment);

        Node* binaryOperator(
                Environment* environment,
                const std::set<Token, std::less<>>&opers,
                std::function<Node*(Environment* envir)> funA,
                std::function<Node*(Environment* envir)> funB=nullptr
                        );
        Node* unaryOperator(
                Environment* environment,
                const std::set<Token, std::less<>>&opers,
                std::function<Node*(Environment* envir)> fun
                );

        uNode new_ExeUnit();        // ExeUnit    : '{' { IfStmt | AssignStmt | Expr } '}'
        uNode new_IfStmt();         // IfStmt     : 'if' Expr ExeUnit 
                                    //              {'elif' Expr ExeUnit }
                                    //              ['else' ExeUnit ]
        uNode new_WhileStmt();      // WhileStmt  : 'while' Expr ExeUnit
        uNode new_AssignStmt();     // AssignStmt : ValBuild
                                    //            | FuncDef
                                    //            | StateDef
        uNode new_ValBuild();       // ValBuild   : PostfixExpr '=' Expr
                                    //            | PostfixExpr '=' '[' [Params] ']'
        uNode new_FuncDef();        // FuncDef    : 'func' IDENT  '(' Params ')'  ExeUnit
        uNode new_StateDef();       // StateDef   : 'sm'   IDENT ['(' Params ')'] ExeUnit
                        
        uNode new_Expr();           // Expr       : LogicExpr
        uNode new_LogicExpr();      // LogicExpr  : ('not' LogicExpr)
                                    //            | (CompExpr {('and' | 'or') CompExpr}) 
        uNode new_CompExpr();       // CompExpr  : ArithExpr {('>' | '<' | '>=' | '<=' | '==') ArithExpr}
        uNode new_ArithExpr();      // ArithExpr  : Term {('+' | '-') Term}
        uNode new_Term();           // Term       : Factor {('*' | '/') Factor}
        uNode new_Factor();         // Factor     : {'+' | '-'} PostfixExpr
        uNode new_PostfixExpr();    // PostfixExpr: Primary
                                    //            | PostfixExpr '(' ExprList ')'
                                    //            | PostfixExpr '[' ExprList ']'
                                    //            | PostfixExpr '.' IDENT '(' ExprList ')'
        uNode new_Primary();        // Primary    : INT_CONST
                                    //            | FLOAT_CONST
                                    //            | STR_CONST
                                    //            | IDENT
                                    //            | '(' ArithExpr ')'
        
        std::vector<std::string> new_Params();  // Params     : [ IDENT { ',' IDENT } ]
        std::vector<uNode> new_ExprList();      // ExprList   : [Expr {',' Expr}]
    };

} // hdg

#endif //HDG_PARSER_H
