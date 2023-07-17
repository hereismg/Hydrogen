//
// Created by Magnesium on 2023/7/11.
//

#include "Token.h"


namespace hdg {

    Token::Token(std::string type, std::string  value, int posStart, int posEnd):
            type(std::move(type)), value(std::move(value)), posStart(posStart), posEnd(posEnd){
    }

    Token::Token(const hdg::Token &tok):
            type(tok.type), value(tok.value), posStart(tok.posStart), posEnd(tok.posEnd){
    }

    Token::~Token() {

    }

    std::string Token::getType() {
        return type;
    }

    std::string Token::getValue() {
        return value;
    }

    void Token::setType(const std::string& type_) {
        this->type = std::move(type);
    }

    void Token::setValue(const std::string& value_) {
        this->value = std::move(value);
    }

    std::ostream& operator<<(std::ostream &out, Token& tok) {
        if (tok.value != NONE){
            std::string str = ":";
            out << tok.type << str << tok.value;
        }else{
            out << tok.type;
        }
        return out;
    }
} // hdg