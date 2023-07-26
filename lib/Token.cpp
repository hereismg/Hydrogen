//
// Created by Magnesium on 2023/7/11.
//

#include "Token.h"


namespace hdg {
//    tokenTypeName = {
//        {INT, "integer"},
//        {FLOAT, "float"},
//        {IDENTIFIER, "identifier"},
//        {KEYWORD, "keyword"},
//
//        {EE, "ee"},
//        {GT, "greaterThan"},
//        {LT, "lessThan"},
//        {GTE, "greaterThanEqual"},
//        {LTE, "lessThanEqual"},
//
//        {PLUS, "plus"},
//        {MINUS, "minus"},
//        {MUL, "multiply"},
//        {DIV, "division"},
//        {POW, "power"},
//
//        {LPAREN, "leftParenthesis"},
//        {RPAREN, "rightParenthesis"},
//        {EQ, "equation"},
//
//        {EF, "endOfFile"},
//        {NONE, "none"}
//    };



    Token::Token(TokenType type, std::string value, const std::string& context, int posStart, int posEnd):
            m_type(type), m_value(std::move(value)), m_position(context, posStart, posEnd){
    }

    Token::Token(TokenType type, std::string value, const std::string &context, int posStart):
        m_type(type), m_value(std::move(value)), m_position(context, posStart, posStart+1){
    }

    Token::Token(TokenType type, const std::string &context, int posStart, int posEnd):
        m_type(type), m_value(""), m_position(context, posStart, posEnd){
    }

    Token::Token(TokenType type, const std::string &context, int posStart):
        m_type(type), m_value(""), m_position(context, posStart, posStart+1){
    }

    Token::Token(const hdg::Token &tok) = default;

    Token::~Token() = default;

    void Token::setType(TokenType type) {
        m_type = type;
    }

    void Token::setValue(const std::string& value) {
        m_value = value;
    }

    TokenType Token::getType() {
        return m_type;
    }

    std::string Token::getValue() {
        return m_value;
    }


    std::ostream& operator<<(std::ostream &out, Token& tok) {
        if (tok.m_value.empty()){
            out << tokenTypeName[tok.m_type];
        }else{
            std::string str = ":";
            out << tokenTypeName[tok.m_type] << str << tok.m_value;
        }
        return out;
    }

    Position &Token::thisPosition() {
        return m_position;
    }


} // hdg