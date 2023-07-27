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
            "true",
            "false",
            "and",
            "or",
    };

    enum LegalChar{
        ILLEGAL = 0,
        DIGITAL = 1,
        LOWERCASE = 2,
        UPPERCASE = 4,
        UNDERLINE = 8
    };

    LegalChar whatIsThis(char c);
    bool whatIsThis(char c, int target);
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
