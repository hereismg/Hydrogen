//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/List.h"

namespace hdg {
    List::List() {
        setClass("List");
    }

    List::List(const std::vector<Object*> &list): m_list(list) {
        setClass("List");
    }

    std::string List::toString() {
        std::stringstream context;
        context << "[";

        if (!m_list.empty()){
            for (int i=0; i<m_list.size()-1; i++){
                context << m_list[i]->toString() << ", ";
            }
            context << (*m_list.rbegin())->toString();
        }
        context << "]";

        return context.str();
    }

    Object *List::plus(Object *other) {
        List* list = (List*)copy();
        list->m_list.push_back(other);
        return list;
    }

    Object *List::equation(Object *other) {
        if (other->getClass() == "List"){
            return new Integer(m_list == ((List*)other)->m_list);
        }
        illegalOperator();
        return nullptr;
    }

    Object *List::brackets(const std::vector<Object *> &args) {
        if (args.size() == 1 && args[0]->getClass() == "Integer"){
            long long index = ((Integer*)args[0])->getValue();
            if (index < m_list.size()){
                return m_list[index];
            }
        }
        illegalOperator();
        return nullptr;
    }

    bool List::isTrue() {
        return !m_list.empty();
    }

    Object *List::copy() {
        return new List(m_list);
    }

    std::vector<Object *> List::getValue() {
        return m_list;
    }


} // hdg