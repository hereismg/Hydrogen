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
#include "../../include/basic/Position.h"

namespace hdg_lexer {
    using uint64 = unsigned long long;
    using uint32 = unsigned int;

    enum class CharType: uint64{
        OTHER       = 0,
        DIGITAL     = 1 << 0,
        HEX_DIGITAL = 1 << 1,
        LOWERCASE   = 1 << 2,
        UPPERCASE   = 1 << 3,
        UNDERLINE   = 1 << 4,
        BLANK       = 1 << 5,
        BRACKET_C     = 1 << 6,
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


    enum class StateType: int{
        START,      // 第一个类型必须是 START
        KEYWORD,
        IDENT,
        INT_CONST,
        BRACKET_S,

        END,

        ACCEPT,
        ERROR = 16,      // 最后一个类型必须是 ERROR，这里设定最多只能有 16 种状态
    };
    static_assert(static_cast<int>(StateType::START) == 0);
    static_assert(static_cast<int>(StateType::ERROR) == 16);

    class Token{
    protected:
        StateType     m_type;
        std::string   m_val;
        hdg::Position m_pos;

    public:
        Token(StateType type, std::string val);

        [[nodiscard]] StateType   getType() const;
        [[nodiscard]] std::string getVal()  const;

        void setType(StateType type);
        void setVal(const std::string& val);

        std::string toString();
    };

    class StateMachine;

    class Event{
    public:
        const char m_currChar;
        const std::shared_ptr<StateMachine>& m_sender;
        Event(char currChar, const std::shared_ptr<StateMachine>& sender);
    };

    /**
     * 抽象状态
     * */
    class AbstractState{
    protected:
        using CondFun = std::function<bool(const Event&)>;
        typedef std::tuple<CharType, StateType, CondFun> Edge;
//        StateMachine *m_machine;
        std::vector<Edge> m_edges;
        bool m_autoNext;

    public:
        explicit AbstractState();
        ~AbstractState() = default;

        void               addEdge(CharType condChar, StateType type, const CondFun& condFun = nullptr);
        virtual StateType  getNextState(const Event& event);
        [[nodiscard]] bool isAutoNext() const;
//        virtual bool accept(char cur);
    };

    class StartState: public AbstractState{
    public:
        explicit StartState();
    };

    class KeywordState: public AbstractState{
    protected:
        std::set<std::string> keywordSet;

    public:
        explicit KeywordState();
    };

    class IdentState: public AbstractState{
    public:
        explicit IdentState();
    };

    class IntConstState: public AbstractState{
    public:
        explicit IntConstState();
    };

    class OperState: public AbstractState{
    public:
        explicit OperState();
//        bool accept(char cur) override;
    };

    class BracketState: public AbstractState{
    public:
        explicit BracketState();
        StateType getNextState(const Event& event) override;
    };

    class ErrorState: public AbstractState{
    public:
        explicit ErrorState();
        StateType getNextState(const Event& event) override;
//        bool accept(char cur) override;
    };

    class AcceptState: public AbstractState{
    public:
        explicit AcceptState();
        StateType getNextState(const Event& event) override;
//        bool accept(char cur) override;
    };

    /**
     * 自动机管理
     * */
    class StateMachine: public std::enable_shared_from_this<StateMachine>{
    protected:
        StateType m_lastState;
        StateType m_currState;
        std::vector<std::shared_ptr<AbstractState>> m_list;

        char m_currChar;
        std::string m_tokenVal;
        std::shared_ptr<StateType> m_token;
        struct StateMachineKey {
            friend class StateMachine;
            StateMachineKey() = default;
        };

    private:
        StateMachine() = default;

    public:
        StateMachine(StateMachineKey){};
        static std::shared_ptr<StateMachine> buildStateMachine();

        void setCurrToken(StateType type);

        std::string getTokenVal();
        StateType getLastState();
        void init();
        void move(StateType target);

        /**
         * @details:
         * 状态机的主要工作如下：
         * 首先更新状态机的 m_currChar，方便操作。
         * 其次，调用当前状态的 accept 方法，传入字符
         * 状态发生改变以后，若返回值为 true，则说明不需要传入新的字符串，再进入到下一个状态中
         * */
        std::shared_ptr<StateType> update(char c);
    };


//    class BaseState;
//
//    class StateMachine;
//
//    using Event = std::variant<int, std::string>;
//
//    enum class StateType: uint32{
//        START,      // 第一个类型必须是 START
//        KEYWORD,
//        IDENT,
//        INT_CONST,
//
//        END,
//
//        ACCEPT,
//        ERROR = 32,      // 最后一个类型必须是 ERROR，这里设定最多只能有 32 种状态
//    };
//
//    /**
//     * 状态基类
//     * 在该类中，本身不存储 StateMachine 类，只在必要的时候传入方法，然后进行相应的逻辑
//     * 因此，在状态类中，只存储对应的“边”，然后利用“事件”的概念判断应该要转移到哪个状态中
//     * 注意：改变状态机的状态应该由 StateMachine 执行
//     * */
//    class BaseState{
//    public:
//        constexpr static const std::string TYPE = "BaseState";
//
//    protected:
//        using Condition = std::function<bool(const Event&)>;
//        std::vector<std::tuple<std::shared_ptr<BaseState>, CharType, Condition>> transitions;
//
//    public:
//        ~BaseState() = default;
//
//        virtual std::string getType() = 0;
//
//        [[nodiscard]] std::shared_ptr<BaseState> getNextState(const Event& event);
//
//        void addTransition(StateType target, CharType condChar, Condition condFun = nullptr);
//
//        virtual void onEnter(StateMachine&){};
//        virtual void onExit(StateMachine&){};
//        virtual void onUpdate(StateMachine&){};
//    };
//
//    /**
//     * 状态机管理类
//     * */
//    class StateMachine{
//    private:
//        std::vector<std::shared_ptr<BaseState>> states;
//
//        std::string currentTokenVal;
//        std::shared_ptr<BaseState> currentState;
//        std::shared_ptr<BaseState> lastState;
//
//    public:
//        StateMachine() = default; // 想办法将该方法私有化
//
//        void registerState(const std::string& name, std::shared_ptr<BaseState> state);
//
//        void initialize(const std::string& initialState);
//
//        void update();
//
//        void handleEvent(const Event& event);
//
//        static std::shared_ptr<StateMachine> buildDefaultMachine();
//    };
//
//    /**
//     * “关键字”状态
//     * */
//    class KeywordState: public BaseState{
//    public:
//        constexpr static const std::string TYPE = "KEYWORD";
//        std::string getType() override;
//    };
//
//    /**
//     * “标识符”状态
//     * */
//    class IdentState: public BaseState{
//    public:
//        constexpr static const std::string TYPE = "IdentState";
//
//        std::string getType() override;
//    };
//
//    /**
//     * “数字常量”状态
//     * */
//    class IntConstState: public BaseState{
//    public:
//        constexpr static const std::string TYPE = "IntConstState";
//        std::string getType() override;
//
//    };
//
//    /**
//     * “异常”状态
//     * */
//    class ErrorState: public BaseState{
//    public:
//        constexpr static const std::string TYPE = "ErrorState";
//        std::string getType() override;
//
//    };
//
//    /**
// * “接受”状态
// * */
//    class AcceptState: public BaseState{
//    public:
//        constexpr static const std::string TYPE = "AcceptState";
//        std::string getType() override;
//
//    };

} // hdg

#endif //HDG_NEWLEXER_H
