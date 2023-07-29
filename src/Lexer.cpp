//
// Created by Magnesium on 2023/7/11.
//

#include "../include/Lexer.h"

namespace hdg {

    LegalChar whatIsThis(char c){
        if (c>='0' && c<='9') return LegalChar::DIGITAL;
        else if (c>='a' && c<='z') return LegalChar::LOWERCASE;
        else if (c>='A' && c <='Z') return LegalChar::UPPERCASE;
        else if (c=='_') return LegalChar::UNDERLINE;
        else return LegalChar::ILLEGAL;
    }

    bool whatIsThis(char c, int target){
        LegalChar what = whatIsThis(c);
        return what & target;
    }

    std::ostream& operator<<(std::ostream& out, std::vector<Token>& tokens) {
        if (tokens.empty()){
            out << "NONE";
        }else{
            out << "[";

            for (int i=0; i<tokens.size()-1; i++) {
                out << tokens[i] << ", ";
            }

            out << tokens[tokens.size()-1] << "]";
        }
        return out;
    }

    Lexer::Lexer(const std::string& text):
            m_text(text), m_currentChar('\0'), m_pos(-1) {
        advance();
    }

    void Lexer::advance() {
        m_currentChar = m_text[++m_pos];
    }

    const std::string& Lexer::getText() {
        return m_text;
    }

    void Lexer::run() {
        while (m_pos < m_text.length()){
            if (m_currentChar == ' ' || m_currentChar == '\n' || m_currentChar == '\t'){
                advance();
            }
            else if (whatIsThis(m_currentChar) == LegalChar::DIGITAL){
                buildNumber();
            }
            else if (whatIsThis(m_currentChar, LegalChar::UNDERLINE | LegalChar::UPPERCASE | LegalChar::LOWERCASE)){
                buildIdentifier();
            }
            else if (m_currentChar == '>'){
                buildGreaterThan();
            }
            else if (m_currentChar == '<'){
                buildLessThan();
            }
            else if (m_currentChar == '='){
                buildEquation();
            }

            else if (m_currentChar == '+'){
                m_tokens.emplace_back(PLUS, m_text, m_pos);
                advance();
            }
            else if (m_currentChar == '-'){
                m_tokens.emplace_back(MINUS, m_text, m_pos);
                advance();
            }
            else if (m_currentChar == '*'){
                m_tokens.emplace_back(MUL, m_text, m_pos);
                advance();
            }
            else if (m_currentChar == '/'){
                m_tokens.emplace_back(DIV, m_text, m_pos);
                advance();
            }
            else if (m_currentChar == '^'){
                m_tokens.emplace_back(POW, m_text, m_pos);
                advance();
            }
            else if (m_currentChar == '('){
                m_tokens.emplace_back(LPAREN, m_text, m_pos);
                advance();
            }
            else if (m_currentChar == ')'){
                m_tokens.emplace_back(RPAREN, m_text, m_pos);
                advance();
            }
            else{
                throw IllegalCharError(
                        m_pos, m_pos + 1, m_text,
                        "Expect digital, '+', '-', '*', '/' or '^'."
                        );
            }
        }
        m_tokens.emplace_back(EF, m_text, m_pos);
    }

    void Lexer::buildNumber() {
        int posStart = m_pos;
        int counter = 0;
        TokenType type = INT;

        while(m_pos < m_text.length() && (whatIsThis(m_currentChar) == LegalChar::DIGITAL || m_currentChar == '.')) {
            if (m_currentChar == '.') {
                if (counter==1) break;
                type = FLOAT;
                counter++;
            }
            advance();
        }

        m_tokens.emplace_back(type, m_text.substr(posStart, m_pos - posStart), m_text, posStart, m_pos);
    }

    std::vector<Token>& Lexer::getTokens() {
        return m_tokens;
    }

    void Lexer::buildGreaterThan() {
        int posStart = m_pos;
        TokenType type = GT;

        advance();

        if (m_pos<m_text.length() && m_currentChar=='='){
            type = GTE;
            advance();
        }

        m_tokens.emplace_back(type, m_text.substr(posStart, m_pos-posStart), m_text, posStart, m_pos);
    }

    void Lexer::buildLessThan() {
        int posStart = m_pos;
        TokenType type = LT;

        advance();

        if (m_pos<m_text.length() && m_currentChar=='='){
            type = LTE;
            advance();
        }

        m_tokens.emplace_back(type, m_text.substr(posStart, m_pos-posStart), m_text, posStart, m_pos);
    }

    void Lexer::buildEquation() {
        int posStart = m_pos;
        TokenType type = EQ;

        advance();

        if (m_pos<m_text.length() && m_currentChar=='='){
            type = EE;
            advance();
        }

        m_tokens.emplace_back(type, m_text.substr(posStart, m_pos-posStart), m_text, posStart, m_pos);
    }

    void Lexer::buildIdentifier() {
        int posStart = m_pos;
        TokenType type = IDENTIFIER;

        advance();

        while(m_pos < m_text.size() && (whatIsThis(m_currentChar, LegalChar::DIGITAL | LegalChar::UPPERCASE | LegalChar::LOWERCASE))){
            advance();
        }

        std::string value = m_text.substr(posStart, m_pos-posStart);

        if (keywordSet.find(value) != keywordSet.end()) type = KEYWORD;

        m_tokens.emplace_back(type, value, m_text, posStart, m_pos);
    }

} // hdg