#include "../../include/object/state_machine.h"

#include "../../include/node/visitor.h"

namespace hdg{
    StateMachine::StateMachine(): m_envir(std::make_shared<New_Environment>()){}

    sStateMachine StateMachine::create(vector<uNode> stmts) {
        auto sm = std::make_shared<StateMachine>();
        sm->m_stmts = std::move(stmts);
        return sm;
    }

    void StateMachine::exe(Visitor& visitor, i32 index) {
        visitor.getStack().push_back(m_envir);

        assert(m_stmts.size() > index);
        m_stmts[index]->accept(visitor);

        visitor.getStack().pop_back();
    }

    void StateMachine::exe(Visitor & visitor, i32 begin, i32 end) {
        visitor.getStack().push_back(m_envir);

        assert(begin >= 0);
        assert(end   <= m_stmts.size());
        
        for (i32 i = begin; i < end; i++){
            m_stmts[i]->accept(visitor);
        }

        visitor.getStack().pop_back();
    }
} // namespace hdg
