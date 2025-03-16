#ifndef HDG_NEWLEXER_H
#define HDG_NEWLEXER_H

#include <variant>
#include <string>
#include <functional>
#include <memory>
#include <tuple>
#include <sml.hpp>
#include <cassert>
#include "../basic/Position.h"

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
    class Event_QUOTE: public Event{
    public:
        explicit Event_QUOTE(std::weak_ptr<Context> ctx): Event(std::move(ctx)){}
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
        NONE,
        KEYWORD,
        IDENT,
        INT_CONST,
        FLOAT_CONST,
        BRACKET_T,
        STR_CONST,
        OPERATOR,
    };

    inline auto INIT        = "INIT"_s;
    inline auto KEYWORD     = "KEYWORD"_s;
    inline auto IDENT       = "IDENT"_s;
    inline auto INT_CONST   = "INT_CONST"_s;
    inline auto FLOAT_CONST = "FLOAT_CONST"_s;
    inline auto STR_CONST   = "STR_CONST"_s;
    inline auto OPERATOR    = "OPERATOR"_s;
    inline auto ERROR       = "ERROR"_s;

    /**
     * @class Token
     * @brief 表示词法分析后生成的词法单元（Token），包含类型、值和位置信息
     * 
     * 该类用于存储词法分析器生成的词法单元信息，包含：
     * - Token 类型（如标识符、数字、运算符等）
     * - Token 在源代码中的实际字符串值
     * - Token 在源代码中的位置信息（用于错误提示和调试）
     */
    class Token {
    protected:
        TokenType     m_type; ///< token 类型（枚举类型，如 IDEN、INT_CONST 等）
        std::string   m_val;  ///< token 在源代码中的实际字符串值
        hdg::Position m_pos;  ///< token 在源代码中的位置信息（行号、列号等）
    
    public:
        /**
         * @brief 默认构造函数，创建空 token
         */
        Token();
        
        /**
         * @brief 带参数的构造函数，创建指定类型的令牌
         * @param type token 类型（TokenType 枚举值）
         * @param val  token 的字符串值
         */
        Token(TokenType type, std::string val);
     
        /**
         * @brief 获取位置信息的引用（允许外部修改位置信息）
         * @return hdg::Position 的位置信息引用
         */
        hdg::Position& thisPosition();
     
        // 设置方法组
        void setType(TokenType type);  ///< 设置令牌类型
        void setVal(std::string val);  ///< 设置令牌字符串值
        
        /**
         * @brief 向 token 值末尾追加字符
         * @param c 要追加的字符
         * 用于词法分析时逐步构建令牌值（例如处理多字符运算符或长数字）
         */
        void pushChar(char c);
        
        /// 重置 token 内容（类型设为默认，值清空，位置不重置）
        void clear();
     
        // 访问方法组
        std::string getVal();    ///< 获取令牌字符串值（const版本建议补充）
        TokenType getType();     ///< 获取令牌类型（const版本建议补充）
        
        /**
         * @brief 比较两个 token 是否相等
         * @param other 要比较的另一个 token
         * @return 当类型和值都相同时返回true
         * @note 不比较位置信息，因为相同代码段可能生成多个位置不同的相同令牌
         */
        bool equal(const Token& other);
    };


    class Context{
    protected:
        Token              m_curToken;
        std::string        m_code;
        hdg::Indicator     m_ptr;
        std::vector<Token> m_tokenArr;

    public:
        Context(std::string code);

        bool advance();
        void pushChar2Token();
        void buildToken(TokenType type);

        size_t      size();
        char        getChar();
        size_t      getPtr();
        std::string getTokenVal();
        std::vector<Token> getTokenArr();
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

    // action
    constexpr auto pushChar2Token = [](const auto& event) {
        event.m_lexer.lock()->pushChar2Token();
    };
    constexpr auto throwError = [](const auto& event) {
        assert(false);
    };
    constexpr auto ignoreChar = [](const auto& event) {
        event.m_lexer.lock()->advance();
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
    constexpr auto buildStrConstToken = [](const auto& event) {
        event.m_lexer.lock()->advance();
        event.m_lexer.lock()->buildToken(TokenType::STR_CONST);
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
                INIT  + event<Event_QUOTE>     / ignoreChar       = STR_CONST,
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
                INT_CONST + event<Event_DOT>       / pushChar2Token     = FLOAT_CONST,
                INT_CONST + event<Event_UPPERCASE> / throwError         = X,
                INT_CONST + event<Event_LOWERCASE> / throwError         = X,
                INT_CONST + event<Event_BLANK>     / buildIntConstToken = INIT,
                INT_CONST + event<Event_BRACKET>   / buildIntConstToken = INIT,
                INT_CONST + event<Event_OPERATOR>  / buildIntConstToken = INIT,

                FLOAT_CONST + event<Event_DIGITAL>   / pushChar2Token       = FLOAT_CONST,
                FLOAT_CONST + event<Event_BLANK>     / buildFloatConstToken = INIT,
                FLOAT_CONST + event<Event_BRACKET>   / buildFloatConstToken = INIT,
                FLOAT_CONST + event<Event_LOWERCASE> / throwError           = X,

                OPERATOR + event<Event_OPERATOR> / pushChar2Token  = OPERATOR,
                OPERATOR + event<Event_DIGITAL>  / buildOperToken  = INIT,
                OPERATOR + event<Event_BRACKET>  / buildOperToken  = INIT,
                
                STR_CONST + event<Event_QUOTE>     / buildStrConstToken = INIT,
                STR_CONST + event<Event_DIGITAL>   / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_UPPERCASE> / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_LOWERCASE> / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_UNDERLINE> / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_OPERATOR>  / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_BRACKET>   / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_BLANK>     / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_OTHER>     / pushChar2Token     = STR_CONST,
                STR_CONST + event<Event_DOT>       / pushChar2Token     = STR_CONST
            );
        }
    };

    
    bool sendEvent(char c, sml::sm<LexerSM>& sm, std::shared_ptr<Context>& ctx);


    std::string debug_CurrentState(sml::sm<LexerSM> &s);

    // class Lexer{
    // protected:
    //     Sender s{},
        
    // public:
    //     Lexer() = default;

    // }
} // hdg

#endif //HDG_NEWLEXER_H
