//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_LEXER_H
#define HDG_LEXER_H

#include<string>
#include<vector>
#include<iostream>
#include<utility>
#include"basic/Token.h"
#include"error/IllegalCharError.h"

namespace hdg {
    const int DIGITAL = 1;
    const int LOWERCASE = 2;
    const int UPPERCASE = 3;

    int whatIsThis(char c);
    std::ostream& operator<<(std::ostream& out, std::vector<Token>& tokens);

    class Lexer {
    private:
        const std::string& text;
        std::vector<Token> tokens;

        char currentChar;
        int pos;

    public:
        explicit Lexer(const std::string& text);
        void advance();

        const std::string& getText();
        std::vector<Token>& getTokens();

        void run();
        void buildNumber();
    };
} // hdg

#endif //HDG_LEXER_H
