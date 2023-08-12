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

    Lexer::Lexer(std::string* text):
            m_text(text), m_currentChar('\0'), m_pos(-1) {
        advance();
    }

    void Lexer::advance() {
        m_currentChar = (*m_text)[++m_pos];
    }

    std::string* Lexer::thisText() {
        return m_text;
    }

    void Lexer::run() {
        while (m_pos < m_text->length()){
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
            else if (m_currentChar == '\"'){
                buildString();
            }
            else if (m_currentChar == '+'){
                m_tokens.emplace_back(PLUS, Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == '-'){
                m_tokens.emplace_back(MINUS, Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == '*'){
                m_tokens.emplace_back(MUL , Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == '/'){
                m_tokens.emplace_back(DIV, Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == '^'){
                m_tokens.emplace_back(POW, Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == '('){
                m_tokens.emplace_back(LPAREN, Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == ')'){
                m_tokens.emplace_back(RPAREN, Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == ':'){
                m_tokens.emplace_back(COLON, Position(m_text, m_pos));
                advance();
            }
            else if (m_currentChar == ','){
                m_tokens.emplace_back(COMMA, Position(m_text, m_pos));
                advance();
            }
            else{
                throw IllegalCharError(
                        "Expect digital, '+', '-', '*', '/' or '^'.",
                        Position(m_text, m_pos)
                        );
            }
        }
        m_tokens.emplace_back(EF, Position(m_text, m_pos));
    }

    void Lexer::buildNumber() {
        int posStart = m_pos;
        int counter = 0;
        TokenType type = INT;

        while(m_pos < m_text->length() && (whatIsThis(m_currentChar) == LegalChar::DIGITAL || m_currentChar == '.')) {
            if (m_currentChar == '.') {
                if (counter==1) break;
                type = FLOAT;
                counter++;
            }
            advance();
        }

        m_tokens.emplace_back(type, m_text->substr(posStart, m_pos - posStart), Position(m_text, posStart, m_pos));
    }

    std::vector<Token>& Lexer::getTokens() {
        return m_tokens;
    }

    void Lexer::buildGreaterThan() {
        int posStart = m_pos;
        TokenType type = GT;

        advance();

        if (m_pos<m_text->length() && m_currentChar=='='){
            type = GTE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_text, posStart, m_pos));
    }

    void Lexer::buildLessThan() {
        int posStart = m_pos;
        TokenType type = LT;

        advance();

        if (m_pos<m_text->length() && m_currentChar=='='){
            type = LTE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_text, posStart, m_pos));
    }

    void Lexer::buildEquation() {
        int posStart = m_pos;
        TokenType type = EQ;

        advance();

        if (m_pos<m_text->length() && m_currentChar=='='){
            type = EE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_text, posStart, m_pos));
    }

    void Lexer::buildIdentifier() {
        int posStart = m_pos;
        TokenType type = IDENTIFIER;

        advance();

        while(m_pos < m_text->size() && (whatIsThis(m_currentChar, LegalChar::DIGITAL | LegalChar::UPPERCASE | LegalChar::LOWERCASE))){
            advance();
        }

        std::string value = m_text->substr(posStart, m_pos-posStart);

        if (keywordSet.find(value) != keywordSet.end()) type = KEYWORD;

        m_tokens.emplace_back(type, value, Position(m_text, posStart, m_pos));
    }

    void Lexer::buildString() {
        std::string str;
        Position pos(m_text, m_pos);
        advance();

        static std::map<char, char> transChar{
                {'n', '\n'},
                {'t', '\t'},
                {'\\', '\\'},
                {'\"', '\"'},
        };

        while (m_pos < m_text->size() && m_currentChar!='\"'){
            if (m_currentChar == '\\'){
                advance();
                auto trans = transChar.find(m_currentChar);
                if (trans != transChar.end()){
                    str += trans->second;
                }
                else{
                    str += ' ';
                }
            }else{
                str += m_currentChar;
            }
            advance();
        }
        advance();
        pos.setPosEnd(m_pos);

        m_tokens.emplace_back(STRING, str, pos);
    }

} // hdg