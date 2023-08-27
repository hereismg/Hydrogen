//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_LEXER_H
#define HDG_LEXER_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include "basic/Token.h"
#include "error/IllegalCharError.h"

namespace hdg {
    static std::set<std::string> keywordSet = {
            "not",
            "and",
            "or",

            "if",
            "elif",
            "else",

            "for",
            "from",
            "to",
            "step",
            "while",

            "function",
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
    protected:
        std::string m_fPath;
        std::string* m_code;
        std::vector<Token> m_tokens;

        char m_currentChar;
        Position::Indicator m_pos;

    public:
        explicit Lexer(std::string fPath, std::string* code);
        std::string getFilePath();
        std::string* thisText();
        std::vector<Token>& getTokens();
        void run();

    protected:
        void advance();

        void buildNumber();
        void buildGreaterThan();
        void buildLessThan();
        void buildEquation();
        void buildIdentifier();
        void buildString();
    };
} // hdg

#endif //HDG_LEXER_H
