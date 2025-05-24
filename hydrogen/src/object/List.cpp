//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/List.h"

// #include <

#include "../../include/object/Integer.h"
#include "../../include/node/visitor.h"

namespace hdg {
    List::List() {
        setClass("List");
    }
    
    List::List(std::vector<sObject>&& list): m_list(std::move(list)) {
        setClass("List");
    }

    List::List(size_t count, sObject obj) : m_list(count, obj){
        setClass("List");
    }

    List::List(const std::vector<Object*> &list): m_list_old(list) {
        setClass("List");
    }

    Object *List::plus(Object *other) {
        List* list = (List*)copy();
        list->m_list_old.push_back(other);
        return list;
    }

    Object *List::equation(Object *other) {
        if (other->getClass_old() == "List"){
            return new Integer(m_list_old == ((List*)other)->m_list_old);
        }
        illegalOperator();
        return nullptr;
    }

    Object *List::brackets(const std::vector<Object *> &args) {
        if (args.size() == 1 && args[0]->getClass_old() == "Integer"){
            int64_t index = ((Integer*)args[0])->getValue();
            if (index < (int64_t)m_list_old.size()){
                return m_list_old[index];
            }
        }
        illegalOperator();
        return nullptr;
    }

    sObject List::equation(sObject other) {
        if (typeid(*other.get()) != typeid(List)) return Integer::False;

        auto& otherList = dynamic_cast<List*>(other.get())->getList();

        if (m_list.size() != otherList.size()) return Integer::False;

        for (size_t i = 0; i < m_list.size(); i++) {
            if (!m_list[i]->equation(otherList[i])->isTrue()) {
                return Integer::False;
            }
        }

        return Integer::True;
    }

    bool List::isTrue() {
        return !m_list_old.empty();
    }

    Object *List::copy() {
        return new List(m_list_old);
    }

    std::vector<Object *> List::getValue() {
        return m_list_old;
    }

    sObject List::plus(sObject other) {
        m_list.emplace_back(other);
        return shared_from_this();
    }

    std::string List::toString() {
        std::stringstream context;
        context << "[";

        if (!m_list.empty()){
            for (size_t i=0; i<m_list.size()-1; i++){
                context << m_list[i]->toString() << ", ";
            }
            context << (*m_list.rbegin())->toString();
        }
        context << "]";

        return context.str();
    }

    sObject List::clone() {
        auto newList = std::make_shared<List>(m_list.size(), nullptr);

        for (size_t i = 0; i < m_list.size(); i++) {
            newList->m_list[i] = m_list[i]->clone();
        }

        return newList;
    }

    sObject List::brackets(const std::vector<sObject>& args, Visitor& visitor) {
        assert(args.size() == 1);

        Object* obj = args[0].get();

        assert(typeid(*obj) == typeid(Integer));

        auto index = dynamic_cast<Integer*>(obj)->getValue();
        
        assert(index >= 0 && index < (int64_t)m_list.size());

        visitor.setRVal(m_list[index]);
        visitor.setLVal(&m_list[index]);

        return m_list[index];
    }
} // hdg