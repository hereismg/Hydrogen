//
// Created by Magnesium on 2023/7/11.
//

#include "Lexer.h"

namespace hdg {

    int whatIsThis(char c){
        if (c>='0' && c<='9') return DIGITAL;
        else if (c>='a' && c<='z') return LOWERCASE;
        else if (c>='A' && c <='Z') return UPPERCASE;
        else return 0;
    }

    std::ostream& operator<<(std::ostream& out, std::vector<Token>& tokens) {
        if (tokens.empty()){
            out << "NONE";
        }else{
            out << "[";
            for (auto & token : tokens){
                out << token << ", ";
            }
            out << "]";
        }
        return out;
    }

    Lexer::Lexer(const std::string& text):
        text(text), currentChar('\0'), pos(-1) {
        advance();
    }

    void Lexer::advance() {
        currentChar = text[++pos];
    }

    const std::string& Lexer::getText() {
        return text;
    }

    void Lexer::run() {
        while (pos<text.length()){
            if (currentChar==' ' || currentChar=='\n'){
                advance();
            }
            else if (whatIsThis(currentChar) == DIGITAL){
                buildNumber();
            }
            else if (currentChar == '+'){
                tokens.emplace_back(TT_PLUS, NONE, text, pos, pos+1);
                advance();
            }
            else if (currentChar == '-'){
                tokens.emplace_back(TT_MINUS, NONE, text, pos, pos+1);
                advance();
            }
            else if (currentChar == '*'){
                tokens.emplace_back(TT_MUL, NONE, text, pos, pos+1);
                advance();
            }
            else if (currentChar == '/'){
                tokens.emplace_back(TT_DIV, NONE, text, pos, pos+1);
                advance();
            }
            else if (currentChar == '^'){
                tokens.emplace_back(TT_POW, NONE, text, pos, pos+1);
                advance();
            }
            else if (currentChar == '('){
                tokens.emplace_back(TT_LPAREN, NONE, text, pos, pos+1);
                advance();
            }
            else if (currentChar == ')'){
                tokens.emplace_back(TT_RPAREN, NONE, text, pos, pos+1);
                advance();
            }
            else{
                throw IllegalCharError(
                        pos, pos+1, text,
                        "Expect digital, '+', '-', '*', '/' or '^'."
                        );
            }
        }
        tokens.emplace_back(TT_EOF, NONE, text, pos, pos+1);
    }

    void Lexer::buildNumber() {
        int posStart = pos;
        int counter = 0;
        std::string type = TT_INT;

        while(pos<text.length() && (whatIsThis(currentChar)==DIGITAL || currentChar=='.')) {
            if (currentChar=='.') {
                if (counter==1) break;
                type = TT_FLOAT;
                counter++;
            }
            advance();
        }

        tokens.emplace_back(type, text.substr(posStart, pos-posStart), text, posStart, pos);
    }

    std::vector<Token>& Lexer::getTokens() {
        return tokens;
    }

} // hdg