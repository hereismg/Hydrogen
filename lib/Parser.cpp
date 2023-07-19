//
// Created by Magnesium on 2023/7/16.
//

#include "Parser.h"

namespace hdg {
    Parser::Parser(std::vector<Token> tokens):
        tokens(std::move(tokens)), currentToken(tokens.begin()){
    }

    void Parser::advance() {
        if (currentToken!=tokens.end())
            currentToken++;
    }
} // hdg