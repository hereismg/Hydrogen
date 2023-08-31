//
// Created by Magnesium on 2023/8/4.
//

#include "../../../include/object/function/Function.h"

namespace hdg {
    Function::Function() = default;

    Function::Function(std::string name, std::vector<ObjAssignNode*>args, Environment* environment, Node* body, const Position& position):
        Object("Function", position), m_name(std::move(name)), m_args(std::move(args)), m_environment(environment), m_body(body){}

    Function::~Function() = default;

    Object *Function::parenthesis(const std::vector<Object*>& list) {
        if (m_args.size() > list.size()){
//            std::stringstream detail;
//            detail << 1;
            throw RuntimeError("too many arg.", m_position);
//            detail << "() missing " << std::to_string(m_args.size()-list.size()) << " required positional argument.";
            return new None;
//            throw RuntimeError("too few args.", m_position);
        }else if (m_args.size() < list.size()){
//            std::string detail =
//                    m_name + "() takes " + std::to_string(m_args.size()) + " positional arguments but " +
//                    std::to_string(list.size()) + " were given.";
            throw RuntimeError("too few arg.", m_position);
            return new None;
//            throw RuntimeError("too many args.", m_position);
        }


        for (int i=0; i<m_args.size(); i++){
            m_environment->setSymbol(m_args[i]->getName(), list[i], 1);
        }

        Object* result = m_body->interpret();
        return result;
    }

    std::string Function::toString() {
        return "<" + m_name + ">";
    }

    Object *Function::copy() {
        return this;
    }

} // hdg