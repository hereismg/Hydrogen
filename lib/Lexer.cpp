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
                tokens.emplace_back(PLUS, text, pos);
                advance();
            }
            else if (currentChar == '-'){
                tokens.emplace_back(MINUS, text, pos);
                advance();
            }
            else if (currentChar == '*'){
                tokens.emplace_back(MUL, text, pos);
                advance();
            }
            else if (currentChar == '/'){
                tokens.emplace_back(DIV, text, pos);
                advance();
            }
            else if (currentChar == '^'){
                tokens.emplace_back(POW, text, pos);
                advance();
            }
            else if (currentChar == '('){
                tokens.emplace_back(LPAREN, text, pos);
                advance();
            }
            else if (currentChar == ')'){
                tokens.emplace_back(RPAREN, text, pos);
                advance();
            }
            else{
                throw IllegalCharError(
                        pos, pos+1, text,
                        "Expect digital, '+', '-', '*', '/' or '^'."
                        );
            }
        }
        tokens.emplace_back(EF, text, pos);
    }

    void Lexer::buildNumber() {
        int posStart = pos;
        int counter = 0;
        TokenType type = INT;

        while(pos<text.length() && (whatIsThis(currentChar)==DIGITAL || currentChar=='.')) {
            if (currentChar=='.') {
                if (counter==1) break;
                type = FLOAT;
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