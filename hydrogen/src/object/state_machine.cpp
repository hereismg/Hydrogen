#include "../../include/object/state_machine.h"

#include "../../include/node/visitor.h"

namespace hdg{
    sStateMachine StateMachine::create(vector<uNode> stmts) {
        auto sm = std::make_shared<StateMachine>();
        sm->m_stmts = std::move(stmts);
        return sm;
    }
} // namespace hdg
