//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_TOKEN_H
#define HDG_TOKEN_H

#include <string>
#include <utility>
#include "Position.h"

namespace hdg {

    const std::string TT_INT = "int";
    const std::string TT_FLOAT = "float";

    const std::string TT_PLUS = "plus";
    const std::string TT_MINUS = "minus";
    const std::string TT_MUL = "mul";
    const std::string TT_DIV = "div";
    const std::string TT_POW = "pow";

    const std::string TT_LPAREN = "lparen";
    const std::string TT_RPAREN = "rparen";

    const std::string TT_EOF = "EOF";
    const std::string NONE = "NONE";


    class Token {
    private:
        std::string type;
        std::string value;

        Position position;

    public:
        Token(std::string type, std::string value, const std::string& context, int posStart, int posEnd);
        Token(const Token& tok);
        ~Token();

        void setType(const std::string& type);
        void setValue(const std::string& value);
        std::string getType();
        std::string getValue();
        Position& thisPosition();

        friend std::ostream& operator<<(std::ostream& out, Token& tok);
    };
} // hdg

#endif //HDG_TOKEN_H
