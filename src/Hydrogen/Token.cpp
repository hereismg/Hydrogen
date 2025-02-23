//
// Created by Magnesium on 2023/7/11.
//

#include "../../include/basic/Token.h"

namespace hdg {
    std::map<Token::Type, std::string> Token::TypeNameMap = {
        {Token::Type::INT,        "INT"},
        {Token::Type::FLOAT,      "FLOAT"},
        {Token::Type::STRING,     "STRING"},
        {Token::Type::IDENTIFIER, "IDENTIFIER"},
        {Token::Type::KEYWORD,    "KEYWORD"},

        {Token::Type::EE,         "EE"},
        {Token::Type::GT,         "GT"},
        {Token::Type::LT,         "LT"},
        {Token::Type::GTE,        "GTE"},
        {Token::Type::LTE,        "LTE"},

        {Token::Type::PLUS,       "PLUS"},
        {Token::Type::MINUS,      "MINUS"},
        {Token::Type::MUL,        "MUL"},
        {Token::Type::DIV,        "DIV"},
        {Token::Type::MOD,        "MOD"},
        {Token::Type::POW,        "POW"},

        {Token::Type::LPAREN,     "LPAREN"},
        {Token::Type::RPAREN,     "RPAREN"},
        {Token::Type::LBRACKET,   "LBRACKET"},
        {Token::Type::RBRACKET,   "RBRACKET"},
        {Token::Type::LBRACE,     "LBRACE"},
        {Token::Type::RBRACE,     "RBRACE"},
        {Token::Type::EQ,         "EQ"},

        {Token::Type::COLON,      "COLON"},
        {Token::Type::COMMA,      "COMMA"},

        {Token::Type::EF,         "EF"},          /// EOF   end of file    由于EOF是C++中的关键字，所以这里用EF代替
        {Token::Type::EL,         "EL"},          /// EOL   end of line    意为“一行的末尾”，这里使用“EL”是为了和上面的”EF“统一表达语言
    };

    Token::Token(){}

    Token::Token(Type type, std::string value, const Position &position):
        m_type(type), m_value(std::move(value)), m_position(position){
    }

    Token::Token(Type type, std::string value):
        m_type(type), m_value(std::move(value)){
    }

    Token::Token(Type type): m_type(type){}

    Token::Token(Type type, const Position &position):
        m_type(type), m_position(position){
    }

    Token::Token(const hdg::Token &tok) = default;

    Token::~Token() = default;

    /**
     * @note cpp里的注释。
     * */
    bool Token::match(Type type, const std::string &value) {
        if (type == m_type && value == m_value) return true;
        else return false;
    }

    void Token::setType(Type type) {
        m_type = type;
    }

    void Token::setValue(const std::string& value) {
        m_value = value;
    }

    Token::Type Token::getType() {
        return m_type;
    }

    std::string Token::getValue() {
        return m_value;
    }


    std::ostream& operator<<(std::ostream &out, Token& tok) {
        out << tok.toString();
        return out;
    }

    Position* Token::thisPosition() {
        return &m_position;
    }

    std::string Token::toString() {
        std::string str;
        if (m_value.empty()){
            str = TypeNameMap[m_type];
        }else{
            str = TypeNameMap[m_type] + ":";
            if (m_type == STRING){
                str += "\"" + m_value + "\"";
            }
            else {
                str += m_value;
            }
        }
        return str;
    }

    bool operator<(const Token &left, const Token &right) {
        if (left.m_type == right.m_type){
            return left.m_value < right.m_value;
        }
        else {
            return left.m_type < right.m_type;
        }
    }
} // hdg