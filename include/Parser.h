//
// Created by Magnesium on 2023/7/16.
//


#ifndef HDG_PARSER_H
#define HDG_PARSER_H

#include <vector>
#include <utility>
#include <functional>
#include <set>
#include <iostream>
#include "basic/Token.h"
#include "basic/Environment.h"
#include "node/Node.h"
#include "node/BinaryOperatorNode.h"
#include "node/UnaryOperatorNode.h"
#include "node/object_node/NumObjNode.h"
#include "node/object_node/ObjAssignNode.h"
#include "node/object_node/ObjAccessNode.h"
#include "node/object_node/FuncObjNode.h"
#include "node/IfNode.h"
#include "node/ForNode.h"
#include "node/WhileNode.h"
#include "error/InvalidSyntaxError.h"

namespace hdg {
    class Parser {
    protected:
        std::vector<Token> m_tokens;
        std::vector<Token>::iterator m_currentToken;
        Environment* m_environment;

    public:
        Parser(std::vector<Token> tokens, Environment* environment);
        Node* run();

    protected:
        void advance();
        void retreat();

        Node* expr(Environment* environment);
        Node* compExpr(Environment* environment);
        Node* arithExpr(Environment* environment);
        Node* term(Environment* environment);
        Node* factor(Environment* environment);
        Node* power(Environment* environment);
        Node* call(Environment* environment);
        Node* atom(Environment* environment);
        Node* ifExpr(Environment* environment);
        Node* forExpr(Environment* environment);
        Node* whileExpr(Environment* environment);
        Node* funcExpr(Environment* environment);

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
    };

} // hdg

#endif //HDG_PARSER_H
