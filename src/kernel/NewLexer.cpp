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

        if (c==' ')              res |= CharType::BLANK;

        if (c=='{' || c=='}' ||
            c=='[' || c==']' ||
            c=='(' || c==')'   ) res |= CharType::BRACKET_C;

        if (c=='>' || c=='<' || c=='=' || c=='|' || c=='&' ||
            c=='+' || c=='-' || c=='*' || c=='/' || c=='^' ||
            c=='!')              res |= CharType::OPERATOR_C;

        return res;
    }

    Token::Token(StateType type, std::string val): m_type(type), m_val(std::move(val)) {}

    StateType Token::getType() const {
        return m_type;
    }

    std::string Token::getVal() const {
        return m_val;
    }

    void Token::setType(StateType type) {
        m_type = type;
    }

    void Token::setVal(const std::string &val) {
        m_val = val;
    }

    std::string Token::toString() {
        return m_val;
    }


    Event::Event(char currChar, const std::shared_ptr<StateMachine>& sender): m_currChar(currChar), m_sender(sender) {}

    AbstractState::AbstractState(): m_autoNext(false) {}

    void AbstractState::addEdge(CharType condChar, StateType type, const CondFun& condFun) {
        m_edges.emplace_back(condChar, type, condFun);
    }

    StateType AbstractState::getNextState(const Event& event){
        auto type = getCharType(event.m_currChar);

        for (auto &[condChar, target, condFun]: m_edges){
            bool cond = true;
            if (condFun != nullptr) cond = condFun(event);

            if(static_cast<uint64>(type & condChar) && cond){
                return target;
            }
        }

        // 若程序来到此处，则说明当前状态有无法处理的字符类型，必须要处理！
        assert(false);
    }

    bool AbstractState::isAutoNext() const {
        return m_autoNext;
    }

    StartState::StartState() {
        addEdge(CharType::LOWERCASE | CharType::UPPERCASE, StateType::KEYWORD);
        addEdge(CharType::UNDERLINE,  StateType::IDENT);
        addEdge(CharType::DIGITAL,    StateType::INT_CONST);
        addEdge(CharType::BLANK,      StateType::START);
        addEdge(CharType::BRACKET_C,  StateType::BRACKET_S);
        addEdge(CharType::OPERATOR_C, StateType::OPERATOR_S);
        addEdge(CharType::ANY,        StateType::ERROR);
    }

    KeywordState::KeywordState() {
        keywordSet.insert({
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
        });

        addEdge(CharType::LOWERCASE | CharType::UPPERCASE, StateType::KEYWORD);
        addEdge(CharType::DIGITAL | CharType::UNDERLINE, StateType::IDENT);
        addEdge(CharType::ANY, StateType::ACCEPT, [this](const Event& event){
            auto txt  = event.m_sender->getTokenVal();
            if(keywordSet.find(txt) == keywordSet.end()){
                event.m_sender->move(StateType::IDENT);
            }
            return true;
        });
//        addEdge(CharType::OTHER, StateType::ERROR);
    }

    IdentState::IdentState(){
        addEdge(CharType::DIGITAL | CharType::LOWERCASE | CharType::UPPERCASE | CharType::UNDERLINE, StateType::IDENT);
        addEdge(CharType::BLANK, StateType::ACCEPT);
        addEdge(CharType::ANY, StateType::ERROR);
    }

    IntConstState::IntConstState() {
        addEdge(CharType::DIGITAL, StateType::INT_CONST);
        addEdge(CharType::BLANK, StateType::ACCEPT);
        addEdge(CharType::ANY, StateType::ERROR);
    }

    OperState::OperState() {

//        addEdge(CharType::)
    };

    BracketState::BracketState() {
        m_autoNext = true;
    }

    StateType BracketState::getNextState(const Event& event) {
        return StateType::ACCEPT;
    }


    ErrorState::ErrorState() {
        m_autoNext = true;
    }

    StateType ErrorState::getNextState(const Event& event) {
        auto lastState = event.m_sender->getLastState();

        if (lastState == StateType::INT_CONST){
            throw hdg::IllegalCharError(
                    "Expect digital.",
                    hdg::Position()
            );
        }else{
            // 若程序在此处，则说明有某种异常没有处理！
            assert(false);
        }
    }

    AcceptState::AcceptState() = default;

    StateType AcceptState::getNextState(const Event& event) {
        return AbstractState::getNextState(event);
    }

    std::shared_ptr<StateMachine> StateMachine::buildStateMachine() {
        auto machine = std::make_shared<StateMachine>(StateMachineKey());

        machine->m_currState = StateType::START;
        machine->m_lastState = StateType::START;
        machine->m_currChar = ' ';

        auto &list = machine->m_list;
        list.resize(static_cast<int>(StateType::ERROR) + 1, nullptr);
        list[static_cast<int>(StateType::START)]      = std::make_shared<StartState>();
        list[static_cast<int>(StateType::KEYWORD)]    = std::make_shared<KeywordState>();
        list[static_cast<int>(StateType::IDENT)]      = std::make_shared<IdentState>();
        list[static_cast<int>(StateType::INT_CONST)]  = std::make_shared<IntConstState>();
        list[static_cast<int>(StateType::BRACKET_S)]  = std::make_shared<BracketState>();
        list[static_cast<int>(StateType::OPERATOR_S)] = std::make_shared<OperState>();

        list[static_cast<int>(StateType::ACCEPT)]    = std::make_shared<AcceptState>();
        list[static_cast<int>(StateType::ERROR)]     = std::make_shared<ErrorState>();

        return machine;
    }

    std::string StateMachine::getTokenVal() {
        return m_tokenVal;
    }

    void StateMachine::move(StateType target) {
        Event event(m_currChar, shared_from_this());
        m_list[static_cast<int>(m_currState)]->onExit(event);
        m_lastState = m_currState;
        m_currState = target;
        m_list[static_cast<int>(m_currState)]->onEnter(event);
    }

    std::vector<Token> StateMachine::update(char c) {
        // 状态机的主要工作如下：
        // 首先更新状态机的 m_currChar，方便操作。
        // 其次，调用当前状态的 accept 方法，传入字符
        // 状态发生改变以后，若返回值为 true，则说明不需要传入新的字符串，再进入到下一个状态中
        assert(m_list[static_cast<int>(m_currState)] != nullptr);

        std::vector<Token> res;

        m_currChar = c;

        Event event(c, shared_from_this());
        do{
            auto nextState = m_list[static_cast<int>(m_currState)]->getNextState(event);

            move(nextState);

            if (m_currState == StateType::ACCEPT){
                // 在这里构建新 token
                res.emplace_back(m_lastState, m_tokenVal);
                init();
                continue;
            }

//            if (m_currChar==' ') continue;
//            else m_tokenVal.push_back(m_currChar);
            m_tokenVal.push_back(m_currChar);
        }
        while(m_list[static_cast<uint64>(m_currState)]->isAutoNext());

        return res;
    }

    StateType StateMachine::getLastState() {
        return m_lastState;
    }

    void StateMachine::init() {
        m_tokenVal.clear();
        m_currState = StateType::START;
        m_lastState = StateType::START;
    }


} // hdg