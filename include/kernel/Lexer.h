//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_LEXER_H
#define HDG_LEXER_H

#include <string>
#include <set>
#include <vector>
#include <tuple>
#include <functional>
#include <memory>
#include "../basic/Token.h"

namespace hdg {

    static std::set<std::string> keywordSet = {
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

    enum LegalChar{
        OTHER       = 0,
        DIGITAL     = 1,
        HEX_DIGITAL = 2,
        LOWERCASE   = 4,
        UPPERCASE   = 8,
        UNDERLINE   = 16,
        BLANK       = 32,
    };


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
    int whatIsThis(char c);
    bool whatIsThis(char c, int target);
    std::ostream& operator<<(std::ostream& out, std::vector<Token>& tokens);

    enum class StatusType: int{
        START,      // 第一个类型必须是 START
        KEYWORD,
        IDENT,
        INT_CONST,

        END,

        ACCEPT,
        ERROR = 16,      // 最后一个类型必须是 ERROR，这里设定最多只能有 16 种状态
    };
    static_assert(static_cast<int>(StatusType::START) == 0);
    static_assert(static_cast<int>(StatusType::ERROR) == 16);

    class StatusMachine;

    class AbstractStatus{
    protected:
        typedef std::tuple<int, StatusType, std::function<bool(char)>> Edge;
        StatusMachine *m_machine;
        std::vector<Edge> m_edges;

    public:
        explicit AbstractStatus(StatusMachine* machine);
        ~AbstractStatus() = default;

        void addEdge(int c, StatusType type, const std::function<bool(char)>& cond = nullptr);
        virtual bool accept(char cur);
    };

    class StartStatus: public AbstractStatus{
    public:
        explicit StartStatus(StatusMachine* machine);
    };

    class KeywordStatus: public AbstractStatus{
    protected:
        std::set<std::string> keywordSet;

    public:
        explicit KeywordStatus(StatusMachine* machine);
    };

    class IdentStatus: public AbstractStatus{
    public:
        explicit IdentStatus(StatusMachine* machine);
    };

    class IntConstStatus: public AbstractStatus{
    public:
        explicit IntConstStatus(StatusMachine* machine);
    };

    class ErrorStatus: public AbstractStatus{
    public:
        explicit ErrorStatus(StatusMachine* machine);
        bool accept(char cur) override;
    };

    class AcceptStatus: public AbstractStatus{
    public:
        explicit AcceptStatus(StatusMachine* machine);
        bool accept(char cur) override;
    };

    class StatusMachine{
    protected:
        StatusType m_lastStatus;
        StatusType m_currStatus;
        std::vector<AbstractStatus*> m_list;

        char m_currChar;
        std::string m_tokenVal;
        std::shared_ptr<StatusType> m_token;

    public:
        StatusMachine();
        ~StatusMachine();

        void setCurrToken(StatusType type);

        std::string getTokenVal();
        StatusType getLastStatus();
        void init();
        void move(StatusType target);

        /**
         * @details:
         * 状态机的主要工作如下：
         * 首先更新状态机的 m_currChar，方便操作。
         * 其次，调用当前状态的 update 方法，传入字符
         * 状态发生改变以后，若返回值为 true，则说明不需要传入新的字符串，再进入到下一个状态中
         * */
        std::shared_ptr<StatusType> accept(char c);
    };


    /**
     * @brief       词法分析器
     * @details     所有传入 Interpreter 的源代码首先都要传入到该类中进行解释，将文本数据加工为 tokens 列表。
     *              并且记录相对行号列号。
     * @attention   词法分析器不存储源代码具体是什么，只记录已经读取过多少行代码。所以，每次调用 run 函数，都要重置 m_pos
     * */

    class Lexer {
    protected:
        std::string m_fPath;
        char m_currentChar{0};
        Indicator m_pos;

        std::string* m_code{nullptr};
        std::vector<Token> m_tokens;

    public:
        Lexer();
        std::string getFilePath();
        std::string* thisText();
        std::vector<Token>& getTokens();


        std::vector<Token> run(const std::string& fPath, std::string* code);

    protected:
        void init();
        void advance();

        void buildNumber();
        void buildGreaterThan();
        void buildLessThan();
        void buildEquation();
        void buildIdentifier();
        void buildString();
    };
} // hdg

#endif //HDG_LEXER_H
