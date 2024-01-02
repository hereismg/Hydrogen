//
// Created by Magnesium on 2023/8/4.
//

#include "../../../include/object/function/Function.h"

namespace hdg {
    Function::Function() {
        setClass("Function");
    }

    Function::Function(std::string name, std::vector<ObjAssignNode*>args, Environment* environment, Node* body, const Position& position):
        m_name(std::move(name)), m_environment(environment), m_body(body){
        setClass("Function");
        m_args = std::move(args);
    }

    Function::~Function() = default;

    Object *Function::parenthesis(const std::vector<Object*>& args) {
        if (m_args.size() != args.size()){
            std::stringstream detail;
            detail << m_name << "(): " <<  std::to_string(m_args.size());

            if (m_args.size()<=1) detail << " argument required, ";
            else detail << " arguments required, ";

            detail << "but " << std::to_string(args.size()) << " received.";
            throw RuntimeError(detail.str());
        }

        for (int i=0; i<m_args.size(); i++){
            m_environment->setSymbol(m_args[i]->getName(), args[i], Environment::Mode::LOCAL);
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