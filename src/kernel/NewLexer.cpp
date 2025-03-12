//
// Created by Magnesium on 2025/3/4.
//

#include <cassert>
#include <set>
#include <utility>
#include "../../include/kernel/NewLexer.h"
#include "../../include/basic/Error.h"
#include "NewLexer.h"


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
            c=='!')              res |= CharType::OPERATOR_C;

        if (c=='"')              res |= CharType::QUOTE;

        if (c=='.')              res |= CharType::DOT;

        return res;
    }

    void Token::setType(TokenType type){
        m_type = type;
    }

    void Token::setVal(std::string val){
        m_val = std::move(val);
    }

    std::string Token::getVal(){
        return m_val;
    }

    TokenType Token::getType(){
        return m_type;
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