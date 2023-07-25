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
#include "Token.h"
#include "node/Node.h"
#include "node/BinaryOperatorNode.h"
#include "node/NumberNode.h"
#include "node/UnaryOperatorNode.h"
#include"error/InvalidSyntaxError.h"

namespace hdg {

    class Parser {
    private:
        std::vector<Token> tokens;
        std::vector<Token>::iterator currentToken;

    public:
        explicit Parser(std::vector<Token> tokens);
        Node* run();

    private:
        void advance();

        Node* expr();
        Node* term();
        Node* factor();
        Node* power();

        Node* binaryOperator(const std::set<std::string>&opers, std::function<Node*()> funA, std::function<Node*()> funB=nullptr);
        Node* unaryOperator();

    };

} // hdg

#endif //HDG_PARSER_H
