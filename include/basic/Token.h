//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_TOKEN_H
#define HDG_TOKEN_H

#include <string>
#include <map>
#include <utility>
#include "Position.h"

namespace hdg {

    enum TokenType{
        INT,
        FLOAT,      // 虽然名称为“float”，但实际上全都是双精度浮点型
        IDENTIFIER,
        KEYWORD,

        EE,         // 逻辑表达式的等于号“==”
        GT,
        LT,
        GTE,
        LTE,

        PLUS,
        MINUS,
        MUL,
        DIV,
        POW,

        LPAREN,
        RPAREN,
        EQ,         // 赋值语句的等于号“=”

        EF,
        NONE
    };

    static std::map<TokenType, std::string> tokenTypeName = {
            {INT,           "INT"},
            {FLOAT,         "FLOAT"},
            {IDENTIFIER,    "IDENTIFIER"},
            {KEYWORD,       "KEYWORD"},

            {EE,            "EE"},
            {GT,            "GT"},
            {LT,            "LT"},
            {GTE,           "GTE"},
            {LTE,           "LTE"},

            {PLUS,          "PLUS"},
            {MINUS,         "MINUS"},
            {MUL,           "MUL"},
            {DIV,           "DIV"},
            {POW,           "POW"},

            {LPAREN,        "LPAREN"},
            {RPAREN,        "RPAREN"},
            {EQ,            "EQ"},

            {EF,            "EF"},          // EOF   end of file    由于EOF是C++中的关键字，所以这里用EF代替
            {NONE,          "NONE"}
    };

    class Token {
    private:
        TokenType m_type;
        std::string m_value;

        Position m_position;

    public:
        Token(TokenType type, std::string value, const Position& position);
        Token(TokenType type, std::string value);
        Token(TokenType type, const Position& position);
        Token(const Token& tok);
        ~Token();

        bool match(TokenType type, const std::string& value);
        void setType(TokenType type);
        void setValue(const std::string& value);
        TokenType getType();
        std::string getValue();
        Position* thisPosition();

        friend std::ostream& operator<<(std::ostream& out, Token& tok);
    };
} // hdg

#endif //HDG_TOKEN_H
