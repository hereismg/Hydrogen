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
#include "node/NumberNode.h"
#include "node/UnaryOperatorNode.h"
#include "node/VariableAssignNode.h"
#include "node/VariableAccessNode.h"
#include "error/InvalidSyntaxError.h"

namespace hdg {

    class Parser {
    private:
        std::vector<Token> m_tokens;
        std::vector<int> m_array;
        std::vector<Token>::iterator m_currentToken;
        Environment* m_environment;

    public:
        Parser(std::vector<Token> tokens, Environment* environment);
        Node* run();

    public:
        void advance();
        void retreat();

        Node* expr();
        void expr(int a);
        Node* compExpr();
        Node* arithExpr();
        Node* term();
        Node* factor();
        Node* power();

        Node* binaryOperator(const std::set<TokenType>&opers, std::function<Node*()> funA, std::function<Node*()> funB=nullptr);
        Node* unaryOperator();

    };

} // hdg

#endif //HDG_PARSER_H
