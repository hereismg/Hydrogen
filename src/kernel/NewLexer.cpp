//
// Created by Magnesium on 2025/3/4.
//

#include <cassert>
#include <set>
#include "../../include/kernel/NewLexer.h"
#include "../../include/basic/Position.h"
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
        if (static_cast<uint64>(state & CharType::BRACKET))     show += "BRACKET | ";

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
            c=='(' || c==')'   ) res |= CharType::BRACKET;

        return res;
    }


    AbstractState::AbstractState(StateMachine *machine): m_machine(machine), m_autoNext(false) {}

    void AbstractState::addEdge(CharType c, StateType type, const std::function<bool(char)>& cond) {
        m_edges.emplace_back(c, type, cond);
    }

    StateType AbstractState::getNextState(Event event){
        auto type = getCharType(event);

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

    bool AbstractState::accept(char cur) {
        auto type = getCharType(cur);

        // 遍历当前节点的邻居节点
        for (auto & [condChar, target, condFun] : m_edges){
            bool cond = true;
            if (condFun != nullptr) cond = condFun(cur);
            if (static_cast<int>(type & condChar) && cond) {
                m_machine->move(target);

                if (target == StateType::ERROR || target == StateType::ACCEPT) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }

        // 若程序来到此处，则说明当前状态有无法处理的字符类型，必须要处理！
        assert(false);
    }

    bool AbstractState::isAutoNext() {
        return m_autoNext;
    }


    StartState::StartState(StateMachine *machine) : AbstractState(machine) {
        addEdge(CharType::LOWERCASE | CharType::UPPERCASE, StateType::KEYWORD);
        addEdge(CharType::UNDERLINE, StateType::IDENT);
        addEdge(CharType::DIGITAL,   StateType::INT_CONST);
        addEdge(CharType::BLANK,     StateType::START);
        addEdge(CharType::BRACKET,   StateType::BRACKET);
        addEdge(CharType::OTHER,     StateType::ERROR);
    }

    KeywordState::KeywordState(StateMachine *machine) : AbstractState(machine) {
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
        addEdge(CharType::BLANK, StateType::ACCEPT, [this](char c){
            auto txt  = this->m_machine->getTokenVal();
            if(keywordSet.find(txt) == keywordSet.end()){
                m_machine->move(StateType::IDENT);
            }
            return true;
        });
        addEdge(CharType::OTHER, StateType::ERROR);
    }

    IdentState::IdentState(StateMachine *machine): AbstractState(machine) {
        addEdge(CharType::DIGITAL | CharType::LOWERCASE | CharType::UPPERCASE | CharType::UNDERLINE, StateType::IDENT);
        addEdge(CharType::BLANK, StateType::ACCEPT);
        addEdge(CharType::OTHER, StateType::ERROR);
    }

    IntConstState::IntConstState(StateMachine *machine): AbstractState(machine) {
        addEdge(CharType::DIGITAL, StateType::INT_CONST);
        addEdge(CharType::BLANK, StateType::ACCEPT);
        addEdge(CharType::OTHER, StateType::ERROR);
    }

    OperState::OperState(StateMachine *machine) : AbstractState(machine) {

    }

    bool OperState::accept(char cur) {
        return AbstractState::accept(cur);
    }

    BracketState::BracketState(StateMachine *machine) : AbstractState(machine) {
        m_autoNext = true;
    }

    StateType BracketState::getNextState(Event event) {
        return StateType::ACCEPT;
    }


    ErrorState::ErrorState(StateMachine *machine): AbstractState(machine) {}

    bool ErrorState::accept(char cur) {
        auto lastState = m_machine->getLastState();

        if (lastState == StateType::INT_CONST){
            throw hdg::IllegalCharError(
                    "Expect digital.",
                    hdg::Position()
            );
        }else{
            // 若程序在此处，则说明有某种异常没有处理！
            assert(false);
        }

        return true;
    }


    AcceptState::AcceptState(StateMachine *machine) : AbstractState(machine) {

    }

    bool AcceptState::accept(char cur) {
        m_machine->setCurrToken(m_machine->getLastState());
        return false;
    }

    StateMachine::StateMachine():
            m_lastState(StateType::START),
            m_currState(StateType::START),
            m_list(static_cast<int>(StateType::ERROR), nullptr),
            m_currChar(' ')
    {
        m_list[static_cast<int>(StateType::START)]     = new StartState(this);
        m_list[static_cast<int>(StateType::KEYWORD)]   = new KeywordState(this);
        m_list[static_cast<int>(StateType::IDENT)]     = new IdentState(this);
        m_list[static_cast<int>(StateType::INT_CONST)] = new IntConstState(this);
        m_list[static_cast<int>(StateType::BRACKET)]   = new BracketState(this);

        m_list[static_cast<int>(StateType::ACCEPT)]    = new AcceptState(this);
        m_list[static_cast<int>(StateType::ERROR)]     = new AcceptState(this);
    }

    StateMachine::~StateMachine() {
        for (auto i: m_list){
            delete i;
        }
    }

    std::string StateMachine::getTokenVal() {
        return m_tokenVal;
    }

    void StateMachine::move(StateType target) {
        m_tokenVal.push_back(m_currChar);
        m_lastState = m_currState;
        m_currState = target;
    }

    std::shared_ptr<StateType> StateMachine::update(char c) {
        // 状态机的主要工作如下：
        // 首先更新状态机的 m_currChar，方便操作。
        // 其次，调用当前状态的 accept 方法，传入字符
        // 状态发生改变以后，若返回值为 true，则说明不需要传入新的字符串，再进入到下一个状态中
        assert(m_list[static_cast<int>(m_currState)] != nullptr);

        m_currChar = c;


        do{
            auto nextState = m_list[static_cast<int>(m_currState)]->getNextState(c);

            m_tokenVal.push_back(c);
            m_lastState = m_currState;
            m_currState = nextState;

            if (m_currState == StateType::ACCEPT){
                auto token = m_lastState;
                init();
                return std::make_shared<StateType>(token);
            }
        }
        while(m_list[static_cast<uint64>(m_currState)]->isAutoNext());

        return nullptr;
    }

    StateType StateMachine::getLastState() {
        return m_lastState;
    }

    void StateMachine::init() {
        m_tokenVal.clear();
        m_currState = StateType::START;
        m_lastState = StateType::START;
        m_token = nullptr;
    }

    void StateMachine::setCurrToken(StateType type) {
        m_token = std::make_shared<StateType>(type);
    }

//    std::shared_ptr<BaseState> BaseState::getNextState(const Event& event){
//        // 遍历当前节点的所有边
//        for (const auto& [target, condChar, condFun] : transitions) {
//            bool cond = true;
//            if (condFun) cond &= condFun(event);
//            char currentCharType = std::get<std::string>(event)[0];
//            if (static_cast<uint64>(getCharType(currentCharType) & condChar) && cond){
//                return target;
//            }
//        }
//
//        // 若没有任何一条边满足条件，那么返回空值
//        return nullptr;
//    }
//
//    void BaseState::addTransition(const std::shared_ptr<BaseState>& target, CharType condChar, Condition condFun){
//        transitions.emplace_back(target, condChar, std::move(condFun));
//    }
//
//    void StateMachine::registerState(const std::string &name, std::shared_ptr<BaseState> state) {
//        states[name] = std::move(state);
//    }
//
//    void StateMachine::handleEvent(const Event &event) {
//        auto nextState = currentState->getNextState(event);
//        if (nextState) {
//            lastState = currentState;
//            currentState = nextState;
//        }
//
//        if (typeid(currentState) == AcceptState){
//
//        }
//    }
//
//
//    std::shared_ptr<StateMachine> StateMachine::buildDefaultMachine(){
//        auto machine = std::make_shared<StateMachine>();
//        machine->states.resize(static_cast<int>(StatesType::ERROR) + 1);
//
//        // 注册状态
//        machine->states[static_cast<int>(StatesType::KEYWORD)]   = std::make_shared<KeywordState>();
//        machine->states[static_cast<int>(StatesType::IDENT)]     = std::make_shared<IdentState>();
//        machine->states[static_cast<int>(StatesType::INT_CONST)] = std::make_shared<IdentState>();
//        machine->states[static_cast<int>(StatesType::ACCEPT)]    = std::make_shared<AcceptState>();
//        machine->states[static_cast<int>(StatesType::ERROR)]     = std::make_shared<ErrorState>();
//
//        keyword->addTransition(keyword, CharType::LOWERCASE);
//        keyword->addTransition(ident,   CharType::DIGITAL | CharType::UPPERCASE | CharType::UNDERLINE);
//        keyword->addTransition(accept,  CharType::BLANK, [](const Event& event){
//            std::set<std::string> keywords = {
//                    "not",
//                    "and",
//                    "or",
//
//                    "if",
//                    "elif",
//                    "else",
//
//                    "for",
//                    "from",
//                    "to",
//                    "step",
//                    "while",
//
//                    "function",
//            };
//            return true;
//        });
//        keyword->addTransition(error,   CharType::OTHER);
//
//        return machine;
//    }
//
//    std::string KeywordState::getType() {
//        return TYPE;
//    }

} // hdg