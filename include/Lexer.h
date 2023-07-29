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
        const std::string& getText();
        std::vector<Token>& getTokens();
        void run();

    private:
        void advance();

        void buildNumber();
        void buildGreaterThan();
        void buildLessThan();
        void buildEquation();
        void buildIdentifier();
    };
} // hdg

#endif //HDG_LEXER_H
