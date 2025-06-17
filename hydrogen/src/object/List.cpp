//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/List.h"

#include "../../include/object/Integer.h"
#include "../../include/object/String.h"
#include "../../include/object/Function.h"
#include "../../include/node/visitor.h"

namespace hdg {
    List::List() {
        m_type = getType();
    }
    
    List::List(std::vector<sObject>&& list): m_list(std::move(list)) {
        m_type = getType();
    }

    List::List(size_t count, sObject obj) : m_list(count, obj) {
        m_type = getType();
    }

    List::List(const std::vector<Object*> &list): m_list_old(list) {
        m_type = getType();
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
        auto opt = List::from(other);

        if (!opt.has_value()) return Integer::False;

        auto otherList = opt.value()->getList();

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

    sList List::append(sObject obj) {
        m_list.emplace_back(std::move(obj));
        return std::dynamic_pointer_cast<List>(shared_from_this());
    }

    sList List::append(int64_t obj) {
        m_list.emplace_back(std::make_shared<Integer>(obj));
        return std::dynamic_pointer_cast<List>(shared_from_this());
    }

    sList List::append(const std::string& obj) {
        m_list.emplace_back(std::make_shared<String>(obj));
        return std::dynamic_pointer_cast<List>(shared_from_this());
    }


    wVarType List::getType() {
        static auto listType = [] {
            auto type = std::make_shared<VarType>("List");

            auto& envir = type->refEnvir();

            {
                auto fun = [](const std::vector<sObject> & args, Visitor & visitor)->sObject{
                    assert(args.size() == 2);

                    auto self = List::from(args[0]).value();

                    self->append(args[1]);

                    std::cout << "String::append" << std::endl;
                    return self;
                };
                std::vector<std::string> args = {"self", "ele"};
                envir.setSymbol("append", std::make_shared<New_BuiltInFunction>(std::move(fun), std::move(args)));
            }


            return type;
        }();

        return listType;
    }

    optional<sList> List::from(const sObject& obj) {
        assert(obj != nullptr);

        if (typeid(*obj) == typeid(List))
            return std::dynamic_pointer_cast<List>(obj);
        else
            return std::nullopt;
    }

    sList List::from(const std::vector<std::string>& list){
        auto res = std::make_shared<List>();
        for (auto& i : list){
            res->getList().push_back(std::make_shared<String>(i));
        }
        return res;
    }

    sList List::from(const std::vector<int64_t>& list){
        auto res = std::make_shared<List>();
        for (auto& i : list){
            res->getList().push_back(std::make_shared<Integer>(i));
        }
        return res;
    }
} // hdg