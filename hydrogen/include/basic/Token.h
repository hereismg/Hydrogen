//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_TOKEN_H
#define HDG_TOKEN_H

#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <nlohmann/json.hpp>

#include "Position.h"


namespace hdg {

    
    class Token {
    public:
        enum Type{
            INT,
            FLOAT,      ///> 虽然名称为“float”，但实际上全都是双精度浮点型
            STRING,
            IDENT,
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

            LPAREN,     ///> 左圆括号 ()
            RPAREN,
            LBRACKET,   ///> 左方括号 []
            RBRACKET,
            LBRACE,     ///> 左花括号 {}
            RBRACE,
            EQ,         ///> 赋值语句的等于号“=”


            COLON,      ///> “:”
            COMMA,      ///> “,”
            DOT,        ///> "."

            EF,         ///> end of file
            EL,         ///> end of line 有两种表达字符：“;” and “\n”
        };

        inline static std::map<Token::Type, std::string> TypeNameMap = {
        {Token::INT,        "INT"},
        {Token::FLOAT,      "FLOAT"},
        {Token::STRING,     "STRING"},
        {Token::IDENT, "IDENTIFIER"},
        {Token::KEYWORD,    "KEYWORD"},

        {Token::EE,         "EE"},
        {Token::GT,         "GT"},
        {Token::LT,         "LT"},
        {Token::GTE,        "GTE"},
        {Token::LTE,        "LTE"},

        {Token::PLUS,       "PLUS"},
        {Token::MINUS,      "MINUS"},
        {Token::MUL,        "MUL"},
        {Token::DIV,        "DIV"},
        {Token::MOD,        "MOD"},
        {Token::POW,        "POW"},

        {Token::LPAREN,     "LPAREN"},
        {Token::RPAREN,     "RPAREN"},
        {Token::LBRACKET,   "LBRACKET"},
        {Token::RBRACKET,   "RBRACKET"},
        {Token::LBRACE,     "LBRACE"},
        {Token::RBRACE,     "RBRACE"},
        {Token::EQ,         "EQ"},

        {Token::COLON,      "COLON"},
        {Token::COMMA,      "COMMA"},

        {Token::EF,         "EF"},          /// EOF   end of file    由于EOF是C++中的关键字，所以这里用EF代替
        {Token::EL,         "EL"},          /// EOL   end of line    意为“一行的末尾”，这里使用“EL”是为了和上面的”EF“统一表达语言
    };

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

        bool match(Type type, const std::string& value) const { return type == m_type && value == m_value; }
        
        void setType(Type type) { m_type = type; }
        
        void setValue(std::string value) { m_value = std::move(value); }
        
        Type getType() const { return m_type; }
        
        std::string getValue() const { return m_value; }

        Position* thisPosition();

        nlohmann::json toJSON() const;

        std::string getClass() const { return "Token"; }

        // mgtodo: 以下内容弃用

        std::string toString();
        friend std::ostream& operator<<(std::ostream& out, Token& tok);
        friend bool operator<(const Token& a, const Token& b);
    };

    // mgtodo: 以下内容弃用
    bool operator<(const Token& left, const Token& right);
    std::string kv_toString(const std::string& key, size_t keyShowLen, const std::string val, size_t valShowLen);
} // hdg

namespace nlohmann {
    template<>
    struct adl_serializer<hdg::Token> {
        static void to_json(json& j, const hdg::Token& t) {
            j = json{
                {"__class__", t.getClass()}, 
                {"type", hdg::Token::TypeNameMap[t.getType()]}, 
                {"value", t.getValue()}  // mgtodo: 很多时候，Token 的 value 都是空的，那么这就看起来很冗余，优化这一点
            };
        }
 
        // static void from_json(const json& j, hdg::Token& p) {
        //     p.setType(j.at("type"));
        // }
    };
}

#endif //HDG_TOKEN_H
