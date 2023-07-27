//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_LEXER_H
#define HDG_LEXER_H

#include<string>
#include<vector>
#include<iostream>
#include<utility>
#include<set>
#include"basic/Token.h"
#include"error/IllegalCharError.h"

namespace hdg {
    static std::set<std::string> keywordSet = {
            "hydrogen",

            "null",
            "and",
            "or",
    };

    const int DIGITAL = 1;
    const int LOWERCASE = 2;
    const int UPPERCASE = 3;

    int whatIsThis(char c);
    std::ostream& operator<<(std::ostream& out, std::vector<Token>& tokens);

    class Lexer {
    private:
        const std::string& m_text;
        std::vector<Token> m_tokens;

        char m_currentChar;
        int m_pos;

    public:
        explicit Lexer(const std::string& text);
        void advance();

        const std::string& getText();
        std::vector<Token>& getTokens();

        void run();
        void buildNumber();
        void buildGreaterThan();
        void buildLessThan();
        void buildEquation();
        void buildIdentifier();
    };
} // hdg

#endif //HDG_LEXER_H
