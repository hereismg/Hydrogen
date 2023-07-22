//
// Created by Magnesium on 2023/7/11.
//

#include<string>
#include <utility>

#ifndef HDG_TOKEN_H
#define HDG_TOKEN_H

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

    const std::string NONE = "NONE";


    class Token {
    private:
        std::string type;
        std::string value;

        int posStart;
        int posEnd;

    public:
        explicit Token(std::string type, std::string value=NONE, int posStart=-1, int posEnd=-1);
        Token(const Token& tok);
        ~Token();

        std::string getType();
        std::string getValue();
        void setType(const std::string& type);
        void setValue(const std::string& value);

        friend std::ostream& operator<<(std::ostream& out, Token& tok);
    };
} // hdg

#endif //HDG_TOKEN_H
