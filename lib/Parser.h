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
        Token* currentToken;

    public:
        explicit Parser(std::vector<Token> tokens);
        void advance();
    };

} // hdg

#endif //HDG_PARSER_H
