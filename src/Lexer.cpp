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

    Lexer::Lexer(): m_pos(0, 0, 0){}

    std::string Lexer::getFilePath() {
        return m_fPath;
    }

    /**
     * @details     初始化函数，运行函数时，会重置 m_pos 方法，并且重置 m_currentChar.
     * */
    void Lexer::init(){
        m_pos.index = 0;
        m_pos.line ++;      ///> 注意，这里不是初始化为1，而是自增一位。这是为了能够记录行数
        m_pos.col = 0;
        m_currentChar = (*m_code)[0];
        m_tokens.clear();
    }

    void Lexer::advance() {
        if (m_pos.index >= m_code->length()) return;
        m_pos.index++;
        m_pos.col++;
        m_currentChar = (*m_code)[m_pos.index];

        if (m_pos.index>0 && (*m_code)[m_pos.index - 1] == '\n') {
            m_pos.line++;
            m_pos.col = 0;
        }
    }

    std::string* Lexer::thisText() {
        return m_code;
    }

    std::vector<Token> Lexer::run(const std::string& fPath, std::string* code) {
        m_fPath = fPath;
        m_code = code;
        init();

        while (m_pos.index < m_code->length()){
            if (m_currentChar == ' ' || m_currentChar == '\t'){
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
            else if (m_currentChar == '\n' || m_currentChar == ';'){
                m_tokens.emplace_back(Token::EL, std::string(1,m_currentChar), Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '+'){
                m_tokens.emplace_back(Token::PLUS, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '-'){
                m_tokens.emplace_back(Token::MINUS, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '*'){
                m_tokens.emplace_back(Token::MUL , Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '/'){
                m_tokens.emplace_back(Token::DIV, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '%'){
                m_tokens.emplace_back(Token::MOD, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '^'){
                m_tokens.emplace_back(Token::POW, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '('){
                m_tokens.emplace_back(Token::LPAREN, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ')'){
                m_tokens.emplace_back(Token::RPAREN, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '['){
                m_tokens.emplace_back(Token::RBRACKET, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ']'){
                m_tokens.emplace_back(Token::LBRACKET, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '{'){
                m_tokens.emplace_back(Token::LBRACE, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '}'){
                m_tokens.emplace_back(Token::RBRACE, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ':'){
                m_tokens.emplace_back(Token::COLON, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ','){
                m_tokens.emplace_back(Token::COMMA, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else{
                throw IllegalCharError(
                        "Expect digital, '+', '-', '*', '/' or '^'.",
                        Position(m_fPath, m_code, m_pos)
                        );
            }
        }
        m_tokens.emplace_back(Token::EF, Position(m_fPath, m_code, m_pos));

        return m_tokens;
    }

    void Lexer::buildNumber() {
        Position::Indicator posStart = m_pos;
        int counter = 0;
        Token::Type type = Token::INT;

        while(m_pos.index < m_code->length() && (whatIsThis(m_currentChar) == LegalChar::DIGITAL || m_currentChar == '.')) {
            if (m_currentChar == '.') {
                if (counter==1) break;
                type = Token::FLOAT;
                counter++;
            }
            advance();
        }

        m_tokens.emplace_back(type, m_code->substr(posStart.index, m_pos.index - posStart.index), Position(m_fPath, m_code, posStart, m_pos));
    }

    std::vector<Token>& Lexer::getTokens() {
        return m_tokens;
    }

    void Lexer::buildGreaterThan() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::GT;

        advance();

        if (m_pos.index < m_code->length() && m_currentChar == '='){
            type = Token::GTE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildLessThan() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::LT;

        advance();

        if (m_pos.index < m_code->length() && m_currentChar == '='){
            type = Token::LTE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildEquation() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::EQ;

        advance();

        if (m_pos.index < m_code->length() && m_currentChar == '='){
            type = Token::EE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildIdentifier() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::IDENTIFIER;

        advance();

        while(m_pos.index < m_code->size() && (whatIsThis(m_currentChar, LegalChar::DIGITAL | LegalChar::UPPERCASE | LegalChar::LOWERCASE | LegalChar::UNDERLINE))){
            advance();
        }

        std::string value = m_code->substr(posStart.index, m_pos.index - posStart.index);

        if (keywordSet.find(value) != keywordSet.end()) type = Token::KEYWORD;

        m_tokens.emplace_back(type, value, Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildString() {
        std::string str;
        Position pos(m_fPath, m_code, m_pos);
        advance();

        static std::map<char, char> transChar{
                {'n', '\n'},
                {'t', '\t'},
                {'\\', '\\'},
                {'\"', '\"'},
        };

        while (m_pos.index < m_code->size() && m_currentChar != '\"'){
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
        pos.setEnd(m_pos);

        m_tokens.emplace_back(Token::STRING, str, pos);
    }

} // hdg