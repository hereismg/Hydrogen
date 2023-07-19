//
// Created by Magnesium on 2023/7/16.
//

#include <vector>
#include <utility>
#include "Token.h"

#ifndef HDG_PARSER_H
#define HDG_PARSER_H

namespace hdg {

    class Parser {
    private:
        std::vector<Token> tokens;
        std::vector<Token>::iterator currentToken;

    public:
        explicit Parser(std::vector<Token> tokens);
        void advance();

        void run();
        void expr();
        void term();
        void factor();
        void power();

        void binaryOperator();
        void unaryOperator();
    };

0} // hdg

#endif //HDG_PARSER_H
