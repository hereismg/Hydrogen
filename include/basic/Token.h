//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_TOKEN_H
#define HDG_TOKEN_H

#include <string>
#include <map>
#include <utility>
#include <iostream>
#include "Position.h"

namespace hdg {

    class Token {
    public:
        enum Type{
            INT,
            FLOAT,      ///> 虽然名称为“float”，但实际上全都是双精度浮点型
            STRING,
            IDENTIFIER,
            KEYWORD,

            NE,         ///> 不等于号“!=”
            EE,         ///> 逻辑表达式的等于号“==”
            GT,
            LT,
            GTE,
            LTE,

            PLUS,
            MINUS,
            MUL,
            DIV,
            MOD,        ///> 百分号”%“，默认为求余符号
            POW,

            LPAREN,     ///> 左圆括号
            RPAREN,
            LBRACKET,   ///> 左方括号
            RBRACKET,
            LBRACE,     ///> 左花括号
            RBRACE,
            EQ,         ///> 赋值语句的等于号“=”


            COLON,      ///> ”:“
            COMMA,      ///> ”,“

            EF,         ///> end of file
            EL,         ///> end of line 有两种表达字符：“;” and “\n”
        };
        static std::map<Type, std::string> TypeNameMap;

    protected:
        Type m_type;
        std::string m_value;

        Position m_position;

    public:
        Token();
        Token(Type type, std::string value, const Position& position);
        Token(Type type, std::string value);
        Token(Type type);
        Token(Type type, const Position& position);
        Token(const Token& tok);
        ~Token();

        /**
         * 用于匹配 Token 的类型与值是否全都相同。
         * @param type  记号类型种类。
         * @param value 该记号类型的值。
         * @return 返回一个布尔值。
         * @note 必须当种类和值全部匹配的时候才会返回 True。
         * */
        bool match(Type type, const std::string& value);
        void setType(Type type);
        void setValue(const std::string& value);
        Type getType();
        std::string getValue();
        Position* thisPosition();
        std::string toString();

        friend std::ostream& operator<<(std::ostream& out, Token& tok);
        friend bool operator<(const Token& a, const Token& b);
    };

    bool operator<(const Token& left, const Token& right);
} // hdg

#endif //HDG_TOKEN_H
