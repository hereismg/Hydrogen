//
// Created by Magnesium on 2025/3/4.
//

#ifndef HDG_NEWLEXER_H
#define HDG_NEWLEXER_H

#include <variant>
#include <string>
#include <functional>
#include <memory>
#include <tuple>
#include <sml.hpp>
#include "../../include/basic/Position.h"

namespace hdg_lexer {
    namespace sml = boost::sml;
        
    using uint64 = unsigned long long;
    using uint32 = unsigned int;
    class LexerSM;
    class Sender;
    class Context;

    enum class CharType: uint64{
        OTHER       = 0,
        DIGITAL     = 1 << 0,
        HEX_DIGITAL = 1 << 1,
        LOWERCASE   = 1 << 2,
        UPPERCASE   = 1 << 3,
        UNDERLINE   = 1 << 4,
        BLANK       = 1 << 5,
        BRACKET_C   = 1 << 6,
        OPERATOR_C  = 1 << 7,
        QUOTE       = 1 << 8,
        DOT         = 1 << 9,

        // 代表任意字符
        ANY         = ~(uint64)0
    };

    constexpr CharType operator|(CharType a, CharType b){
        return static_cast<CharType>(static_cast<int>(a) | static_cast<int>(b));
    }

    constexpr CharType operator&(CharType a, CharType b){
        return static_cast<CharType>(static_cast<int>(a) & static_cast<int>(b));
    }

    constexpr void operator|=(CharType &a, CharType b){
        auto temp = static_cast<CharType>(static_cast<int>(a) | static_cast<int>(b));
        a = temp;
    }

    std::string showCharType(CharType state);

    /**
     * @details 从低位到高位，分别代表：
     *          DIGIT     ::= '0' | '1' | ... | '9'
     *          HEX_DIGIT ::= DIGIT |
     *                        'a'   | ... | 'f' |
     *                        'A'   | ... | 'F'
     *          LOWERCASE ::= 'a' | 'b' | ... | 'z'
     *          UPPERCASE ::= 'A' | 'B' | ... | 'Z'
     *          UNDERLINE ::= '_'
     * */
    CharType getCharType(char c);


    // 定义事件，也就是“终结符”，状态机将根据终结符转移状态
    // 事件中将会引用 Sender 对象，该对象中存储着 SM 的当前状态
    class Event{
    public:
        char m_curChar{' '};
        std::weak_ptr<Context> m_lexer;
        explicit Event(std::weak_ptr<Context> ctx): m_lexer(std::move(ctx)){}
    };

    class Event_OTHER: public Event{
    public:
        explicit Event_OTHER(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_DIGITAL: public Event{
    public:
        explicit Event_DIGITAL(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_LOWERCASE: public Event{
    public:
        explicit Event_LOWERCASE(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_UPPERCASE: public Event{
    public:
        explicit Event_UPPERCASE(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_BLANK: public Event{
    public:
        explicit Event_BLANK(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_BRACKET: public Event{
    public:
        explicit Event_BRACKET(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_DOT: public Event{
    public:
        explicit Event_DOT(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_UNDERLINE: public Event{
    public:
        explicit Event_UNDERLINE(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };
    class Event_OPERATOR: public Event{
    public:
        explicit Event_OPERATOR(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
    };


    // 定义依赖
    class Sender {
    public:
        std::string tokenVal;

        template<class TMsg>
        constexpr void send(const TMsg& msg) { std::printf("send: %d\n", msg.id); }
    };

    using namespace sml;
    enum class TokenType: uint64{
        KEYWORD,
        IDENT,
        INT_CONST,
        FLOAT_CONST,
        BRACKET_T,
        STR_CONST,
        OPERATOR,
    };

    auto INIT        = "INIT"_s;
    auto KEYWORD     = "KEYWORD"_s;
    auto IDENT       = "IDENT"_s;
    auto INT_CONST   = "INT_CONST"_s;
    auto FLOAT_CONST = "FLOAT_CONST"_s;
    auto OPERATOR    = "OPERATOR"_s;
    auto ERROR       = "ERROR"_s;


    class Token{
    public:
        TokenType m_type;
        std::string m_val;
        Token(TokenType type, std::string val): m_type(type), m_val(std::move(val)){}

        void setType(TokenType type){
            m_type = type;
        }

        void setVal(std::string val){
            m_val = std::move(val);
        }

        std::string getVal(){
            return m_val;
        }

        TokenType getType(){
            return m_type;
        }
    };

    class Context{
        public:
            std::string m_tokenVal;
            std::string m_code;
    
            size_t m_ptr;
            std::vector<Token> m_tokenArr;
    
            Context(std::string code):m_code(std::move(code)), m_ptr(0){}
    
            size_t size(){
                return m_code.size();
            }

            char getChar(){
                assert(m_ptr < m_code.size());
                char c = m_code[m_ptr];
                return c;
            }

            auto getTokenArr(){
                return m_tokenArr;
            }

            size_t getPtr(){
                return m_ptr;
            }
    
            std::string getTokenVal(){
                return m_tokenVal;
            }
    
            void pushChar2Token(){
                m_tokenVal.push_back(m_code[m_ptr]);
                ++ m_ptr;
            }
    
            void ignoreChar(){
                ++ m_ptr;
            }
    
            void buildToken(TokenType type){
                m_tokenArr.emplace_back(type, m_tokenVal);
                m_tokenVal.clear();
            }
    
            // void buildBraketToken(){
            //     pushChar2Token();
            //     buildToken();
            // }
        };

    // guard 的定义必须在 event 之后！
    constexpr auto isKeyword = [](const auto& event){
        std::set<std::string> keywordSet = {
                "not",
                "and",
                "or",

                "if",
                "elif",
                "else",

                "for",
                "from",
                "to",
                "step",
                "while",

                "function",
        };
        if (keywordSet.find(event.m_lexer.lock()->getTokenVal()) != keywordSet.end()) return true;
        else return false;
    };

//    constexpr auto isDigital = [](const auto& event){
//        if (static_cast<int>(event.type & CharType::DIGITAL)) return true;
//        else return false;
//    };

    // action
    constexpr auto pushChar2Token = [](const auto& event) {
        event.m_lexer.lock()->pushChar2Token();
    };
    constexpr auto throwError = [](const auto& event) {
        assert(false);
    };
    // constexpr auto buildToken = [](const auto& event) {
    //     event.m_lexer.lock()->buildToken();
    // };
    constexpr auto ignoreChar = [](const auto& event) {
        event.m_lexer.lock()->ignoreChar();
    };
    constexpr auto buildBraketToken = [](const auto& event) {
        event.m_lexer.lock()->pushChar2Token();
        event.m_lexer.lock()->buildToken(TokenType::BRACKET_T);
    };
    constexpr auto buildKeywordToken = [](const auto& event) {
        event.m_lexer.lock()->buildToken(TokenType::KEYWORD);
    };
    constexpr auto buildIdentToken = [](const auto& event) {
        event.m_lexer.lock()->buildToken(TokenType::IDENT);
    };
    constexpr auto buildIntConstToken = [](const auto& event) {
        event.m_lexer.lock()->buildToken(TokenType::INT_CONST);
    };
    constexpr auto buildFloatConstToken = [](const auto& event) {
        event.m_lexer.lock()->buildToken(TokenType::FLOAT_CONST);
    };
    constexpr auto buildOperToken = [](const auto& event) {
        event.m_lexer.lock()->buildToken(TokenType::OPERATOR);
    };


    // 定义状态机
    struct LexerSM{
        auto operator()() const{
            using namespace sml;

            return make_transition_table(
                *INIT + event<Event_DIGITAL>   / pushChar2Token   = INT_CONST,
                INIT  + event<Event_UPPERCASE> / pushChar2Token   = IDENT,
                INIT  + event<Event_LOWERCASE> / pushChar2Token   = KEYWORD,
                INIT  + event<Event_UNDERLINE> / pushChar2Token   = IDENT,
                INIT  + event<Event_OPERATOR>  / pushChar2Token   = OPERATOR,
                INIT  + event<Event_BRACKET>   / buildBraketToken = INIT,
                INIT  + event<Event_BLANK>     / ignoreChar       = INIT,
                INIT  + event<Event_OTHER>     / throwError       = ERROR,
                INIT  + event<Event_DOT>       / throwError       = X,

                KEYWORD + event<Event_DIGITAL>   / pushChar2Token = IDENT,
                KEYWORD + event<Event_UPPERCASE> / pushChar2Token = IDENT,
                KEYWORD + event<Event_LOWERCASE> / pushChar2Token = KEYWORD,
                KEYWORD + event<Event_UNDERLINE> / pushChar2Token = IDENT,
                KEYWORD + event<Event_BRACKET> [isKeyword] / buildKeywordToken = INIT,
                KEYWORD + event<Event_BRACKET>             / buildIdentToken   = INIT,
                KEYWORD + event<Event_BLANK> [isKeyword]   / buildKeywordToken = INIT,
                KEYWORD + event<Event_BLANK>               / buildIdentToken   = INIT,
                KEYWORD + event<Event_OTHER> [isKeyword]   / buildKeywordToken = INIT,
                KEYWORD + event<Event_DOT>                 / throwError       = X,

                IDENT + event<Event_UPPERCASE> / pushChar2Token  = IDENT,
                IDENT + event<Event_DIGITAL>   / pushChar2Token  = IDENT,
                IDENT + event<Event_LOWERCASE> / pushChar2Token  = IDENT,
                IDENT + event<Event_UNDERLINE> / pushChar2Token  = IDENT,
                IDENT + event<Event_BLANK>     / buildIdentToken = INIT,
                IDENT + event<Event_DOT>       / buildIdentToken = INIT,

                INT_CONST + event<Event_DIGITAL>   / pushChar2Token     = INT_CONST,
                INT_CONST + event<Event_BLANK>     / buildIntConstToken = INIT,
                INT_CONST + event<Event_BRACKET>   / buildIntConstToken = INIT,
                INT_CONST + event<Event_DOT>       / pushChar2Token     = FLOAT_CONST,
                INT_CONST + event<Event_OPERATOR>  / buildIntConstToken = INIT,
                INT_CONST + event<Event_UPPERCASE> / throwError         = X,
                INT_CONST + event<Event_LOWERCASE> / throwError         = X,

                FLOAT_CONST + event<Event_DIGITAL>   / pushChar2Token       = FLOAT_CONST,
                FLOAT_CONST + event<Event_BLANK>     / buildFloatConstToken = INIT,
                FLOAT_CONST + event<Event_BRACKET>   / buildFloatConstToken = INIT,
                FLOAT_CONST + event<Event_LOWERCASE> / throwError           = X,

                OPERATOR + event<Event_OPERATOR> / pushChar2Token  = OPERATOR,
                OPERATOR + event<Event_DIGITAL>  / buildOperToken  = INIT,
                OPERATOR + event<Event_BRACKET>  / buildOperToken  = INIT
                // INIT + event<UNDERLINE> / tran = IDENT,
                // INIT + event<UNDERLINE> / tran = IDENT,
                // INIT + event<OTHER> / tran = IDENT,

                // KEYWORD + event<UPPERCASE>  / tran  = KEYWORD,
                // KEYWORD + event<DIGITAL>    / tran  = IDENT,
                // KEYWORD + event<DIGITAL>    / build = INIT
            );
        }
    };

    
    bool sendEvent(char c, sml::sm<LexerSM>& sm, std::shared_ptr<Context>& ctx);


    std::string debug_CurrentState(sml::sm<LexerSM> &s);
} // hdg

#endif //HDG_NEWLEXER_H
