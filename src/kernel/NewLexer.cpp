//
// Created by Magnesium on 2025/3/4.
//

#include <cassert>
#include <set>
#include <utility>
#include "../../include/kernel/NewLexer.h"
#include "../../include/basic/Error.h"


namespace hdg_lexer {

    std::string showCharType(CharType state){
        std::string show;

        if (static_cast<uint64>(state & CharType::DIGITAL))     show += "DIGITAL | ";
        if (static_cast<uint64>(state & CharType::HEX_DIGITAL)) show += "HEX_DIGITAL | ";
        if (static_cast<uint64>(state & CharType::LOWERCASE))   show += "LOWERCASE | ";
        if (static_cast<uint64>(state & CharType::UPPERCASE))   show += "UPPERCASE | ";
        if (static_cast<uint64>(state & CharType::UNDERLINE))   show += "UNDERLINE | ";
        if (static_cast<uint64>(state & CharType::BLANK))       show += "BLANK | ";
        if (static_cast<uint64>(state & CharType::BRACKET_C))   show += "BRACKET_C | ";
        if (static_cast<uint64>(state & CharType::OPERATOR_C))  show += "OPERATOR_C | ";
        if (static_cast<uint64>(state & CharType::DOT))         show += "DOT | ";

        if (show.empty()) show += "OTHER";
        else {
            show = show.substr(0, show.size() - 3);  // 移除末尾的 " | "
        }

        return show;
    }


    CharType getCharType(char c){
        auto res = CharType::OTHER;

        if (c>='0' && c<='9')    res |= CharType::DIGITAL;

        if (c>='0' && c<='9' ||
            c>='a' && c<='f' ||
            c>='A' && c<='F'   ) res |= CharType::HEX_DIGITAL;

        if (c>='a' && c<='z')    res |= CharType::LOWERCASE;

        if (c>='A' && c<='Z')    res |= CharType::UPPERCASE;

        if (c=='_')              res |= CharType::UNDERLINE;

        if (c==' ' || c=='\t')   res |= CharType::BLANK;

        if (c=='{' || c=='}' ||
            c=='[' || c==']' ||
            c=='(' || c==')'   ) res |= CharType::BRACKET_C;

        if (c=='>' || c=='<' || c=='=' || c=='|' || c=='&' ||
            c=='+' || c=='-' || c=='*' || c=='/' || c=='^' ||
            c=='!' || c=='%')    res |= CharType::OPERATOR_C;

        if (c=='"')              res |= CharType::QUOTE;

        if (c=='.')              res |= CharType::DOT;

        return res;
    }

    Token::Token(): m_type(TokenType::NONE), m_val(""){}

    Token::Token(TokenType type, std::string val): m_type(type), m_val(std::move(val)){}

    hdg::Position& Token::thisPosition(){
        return m_pos;
    }

    void Token::setType(TokenType type){
        m_type = type;
    }

    void Token::setVal(std::string val){
        m_val = std::move(val);
    }

    void Token::pushChar(char c){
        m_val.push_back(c);
    }

    void Token::clear(){
        m_type = TokenType::NONE;
        m_val.clear();
    }

    std::string Token::getVal(){
        return m_val;
    }

    TokenType Token::getType(){
        return m_type;
    }

    Context::Context(std::string code): m_code(std::move(code)){}

    bool Context::advance(){
        if (m_ptr.index >= m_code.size()) return false;
        
        ++ m_ptr.index;

        if (m_code[m_ptr.index] == '\n'){
            ++ m_ptr.line;
            m_ptr.col = 1;
        }
        else{
            ++ m_ptr.col;
        }
        return true;
    }

    size_t Context::size(){
        return m_code.size();
    }

    char Context::getChar(){
        assert(m_ptr.index < m_code.size());
        char c = m_code[m_ptr.index];
        return c;
    }

    void Context::pushChar2Token(){
        if (m_curToken.getVal().empty()) m_curToken.thisPosition().setStart(m_ptr);

        m_curToken.pushChar(m_code[m_ptr.index]);

        advance();
    }

    void Context::buildToken(TokenType type){
        // 开始构建 Token
        m_curToken.setType(type);
        m_curToken.thisPosition().setEnd(m_ptr);
        
        // 将 Token 压入列表中
        m_tokenArr.push_back(m_curToken);

        // 清空 Token
        m_curToken.clear();
    }

    std::vector<Token> Context::getTokenArr(){
        return m_tokenArr;
    }

    size_t Context::getPtr(){
        return m_ptr.index;
    }

    std::string Context::getTokenVal(){
        return m_curToken.getVal();
    }

    bool sendEvent(char c, sml::sm<LexerSM> &sm, std::shared_ptr<Context> &ctx)
    {
        if (static_cast<int>(getCharType(c) & CharType::LOWERCASE)){
            return sm.process_event(Event_LOWERCASE(ctx));
        }
        else if (static_cast<int>(getCharType(c) & CharType::UPPERCASE)){
            return sm.process_event(Event_UPPERCASE(ctx));
        }
        else if (static_cast<int>(getCharType(c) & CharType::DIGITAL)){
            return sm.process_event(Event_DIGITAL(ctx));
        }
        else if (static_cast<int>(getCharType(c) & CharType::UNDERLINE)){
            return sm.process_event(Event_UNDERLINE(ctx));
        }
        else if (static_cast<int>(getCharType(c) & CharType::BLANK)){
            return sm.process_event(Event_BLANK(ctx));
        }
        else if (static_cast<int>(getCharType(c) & CharType::BRACKET_C)){
            return sm.process_event(Event_BRACKET(ctx));
        }
        else if (static_cast<int>(getCharType(c) & CharType::OPERATOR_C)){
            return sm.process_event(Event_OPERATOR(ctx));
        }
        else if (static_cast<int>(getCharType(c) & CharType::DOT)){
            return sm.process_event(Event_DOT(ctx));
        }
        else{
            // 程序不应该进行到此处！
            assert(false);
        }
    }

    std::string debug_CurrentState(sml::sm<LexerSM> &s){
        // auto r = s.is();
        if (s.is(INIT)) {
            return "INIT";
        }
        if (s.is(KEYWORD)) {
            return "KEYWORD";
        }
        if (s.is(IDENT)) {
            return "IDENT";
        }
        if (s.is(INT_CONST)) {
            return "INT_CONST";
        }
        if (s.is(FLOAT_CONST)) {
            return "FLOAT_CONST";
        }
        if (s.is(OPERATOR)) {
            return "OPERATOR";
        }
        if (s.is(ERROR)) {
            return "ERROR";
        }
        return "UNKNOWN";
    }
} // hdg