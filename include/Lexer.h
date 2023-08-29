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

    /**
     * @brief       词法分析器
     * @details     所有传入 Interpreter 的源代码首先都要传入到该类中进行解释，将文本数据加工为 toknes 列表。
     *              并且记录相对行号列号。
     * @attention   词法分析器不存储源代码具体是什么，只记录已经读取过多少行代码。所以，每次调用 run 函数，都要重置 m_pos
     * */

    class Lexer {
    protected:
        std::string m_fPath;
        char m_currentChar{0};
        Position::Indicator m_pos;

        std::string* m_code{nullptr};
        std::vector<Token> m_tokens;

    public:
        Lexer();
        std::string getFilePath();
        std::string* thisText();
        std::vector<Token>& getTokens();
        std::vector<Token> run(const std::string& fPath, std::string* code);

    protected:
        void init();
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
