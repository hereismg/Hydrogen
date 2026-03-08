#include "../../include/object/state_machine.h"

#include "../../include/node/visitor.h"
#include "../../include/object/Integer.h"

namespace hdg{
    StateMachine::StateMachine(): m_envir(std::make_shared<New_Environment>()){}

    sStateMachine StateMachine::create(vector<uNode> stmts) {
        auto sm = std::make_shared<StateMachine>();
        sm->m_stmts = std::move(stmts);
        return sm;
    }

    void StateMachine::exe(Visitor& visitor, i32 index) {
        visitor.getStack().push_back(m_envir);

        assert(index >= 0 && static_cast<size_t>(index) < m_stmts.size());
        m_stmts[index]->accept(visitor);

        visitor.getStack().pop_back();
    }

    void StateMachine::exe(Visitor & visitor, i32 begin, i32 end) {
        visitor.getStack().push_back(m_envir);

        assert(begin >= 0);
        assert(end >= 0 && static_cast<size_t>(end) <= m_stmts.size());

        for (i32 i = begin; i < end; i++){
            m_stmts[i]->accept(visitor);
        }

        visitor.getStack().pop_back();
    }

    sObject StateMachine::brackets(const vector<sObject>& args, Visitor& visitor) {
        assert(args.size() >= 1 && args.size() <= 2);
        auto left = Integer::from(args[0])->getValue();
        if (args.size() == 2) auto right = Integer::from(args[1])->getValue();

        

        return nullptr;
    }
} // namespace hdg
