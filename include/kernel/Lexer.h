//
// Created by Magnesium on 2023/7/11.
//

#ifndef HDG_LEXER_H
#define HDG_LEXER_H

#include <string>
#include <set>
#include <vector>
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

    enum StatusType{
        START,      // 第一个类型必须是 START
        KEYWORD,
        IDENT,
        INT_CONST,

        JUDGER,
        ACCEPT,
        ERROR,

        END         // 最后一个类型必须是 END
    };

    class StatusMachine;

    class Status{
    protected:
        typedef std::pair<int, StatusType> Edge;
        StatusMachine *m_machine;
        std::vector<Edge> m_map;

    public:
        explicit Status(StatusMachine* machine);
        ~Status() = default;
        void accept(char cur);
    };

    class StartStatus: public Status{
    public:
        explicit StartStatus(StatusMachine* machine);
    };

    class KeywordStatus: public Status{
    public:
        explicit KeywordStatus(StatusMachine* machine);
    };

    class IdentStatus: public Status{
    public:
        explicit IdentStatus(StatusMachine* machine);

    };

    class IntConstStatus: public Status{
    public:
        explicit IntConstStatus(StatusMachine* machine);

    };

    class ErrorStatus: public Status{
    public:
        explicit ErrorStatus(StatusMachine* machine);
    };

    class JudgerStatus: public Status{
    public:
        explicit JudgerStatus(StatusMachine* machine);
    };

    class StatusMachine{
    protected:
        int m_lastStatus;
        int m_cur;
        std::vector<Status*> m_list;

    public:
        StatusMachine();
        ~StatusMachine();

        void move(StatusType target);

        void accept(char c){
            m_list[m_cur]->accept(c);
        }

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
        Position::Indicator m_pos;

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
