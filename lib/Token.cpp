//
// Created by Magnesium on 2023/7/11.
//

#include "Token.h"


namespace hdg {

    Token::Token(std::string type, std::string value, const std::string& context, int posStart, int posEnd):
            type(std::move(type)), value(std::move(value)), position(context, posStart, posEnd){
    }

    Token::Token(const hdg::Token &tok):
            type(tok.type), value(tok.value), position(tok.position){
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

    Position &Token::thisPosition() {
        return position;
    }

} // hdg