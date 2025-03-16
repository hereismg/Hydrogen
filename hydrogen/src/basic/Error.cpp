//
// Created by Magnesium on 2023/7/16.
//

#include "../../include/basic/Error.h"

namespace hdg {
    Error::Error() = default;

    Error::Error(std::string name): m_name(std::move(name)){}

    Error::Error(std::string name, std::string detail):
    m_name(std::move(name)), m_detail(std::move(detail)) {}

    Error::Error(std::string name, std::string detail, const Position& position):
        m_name(std::move(name)), m_detail(std::move(detail)){
        m_posStack.emplace_back(position);
    }


    void Error::setName(const std::string& name) {
        m_name = name;
    }

    void Error::setDetail(const std::string& detail) {
        m_detail = detail;
    }

    std::vector<Position>* Error::thisPosStack(){
        return &m_posStack;
    }

    std::string Error::toString() {
        std::stringstream information;
        for (auto & iter : std::ranges::reverse_view(m_posStack))
            information << iter.toString() << std::endl;

        information << m_name << ": " << m_detail << std::endl;
        return information.str();
    }

    IllegalCharError::IllegalCharError(std::string details, const Position& position):
            Error("IllegalCharError", std::move(details), position){

    }

    InvalidSyntaxError::InvalidSyntaxError(std::string detail, const Position& position):
            Error("InvalidSyntaxError", std::move(detail), position){
    }

    NotImplementedError::NotImplementedError() {
        m_name = "NotImplementedError";
        m_detail = "not implemented error.";
    }

    RuntimeError::RuntimeError(): Error("RuntimeError"){}

    RuntimeError::RuntimeError(std::string detail):
            Error("RuntimeError", std::move(detail)) {}

    RuntimeError::RuntimeError(std::string details, const Position& position):
            Error("RuntimeError", std::move(details), position){}

    RuntimeError::RuntimeError(std::string name, std::string detail, const Position &position) :
            Error(std::move(name), std::move(detail), position) {}

    ZeroDivisionError::ZeroDivisionError() {
        m_name = "ZeroDivisionError";
        m_detail = "Integer division or modulo by zero.";
    }


} // hdg