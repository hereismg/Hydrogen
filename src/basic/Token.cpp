//
// Created by Magnesium on 2023/7/11.
//

#include "../../include/basic/Token.h"

namespace hdg {
    Token::Token(TokenType type, std::string value, const Position &position):
        m_type(type), m_value(std::move(value)), m_position(position){
    }

    Token::Token(TokenType type, std::string value):
        m_type(type), m_value(std::move(value)), m_position(nullptr, -1){
    }

    Token::Token(TokenType type):
        m_type(type), m_position(nullptr, -1){

    }

    Token::Token(TokenType type, const Position &position):
        m_type(type), m_position(position){
    }

    Token::Token(const hdg::Token &tok) = default;

    Token::~Token() = default;

    bool Token::match(TokenType type, const std::string &value) {
        if (type == m_type && value == m_value) return true;
        else return false;
    }

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
        out << tok.toString();
        return out;
    }

    Position* Token::thisPosition() {
        return &m_position;
    }

    std::string Token::toString() {
        std::string str;
        if (m_value.empty()){
            str = tokenTypeName[m_type];
        }else{
            str = tokenTypeName[m_type] + ":" + m_value;
        }
        return str;
    }

    bool operator<(Token a, Token b){
        if (a.getType()==b.getType()){
            return a.getValue() < a.getValue();
        }
        else {
            return a.getType() < b.getType();
        }
    }

} // hdg