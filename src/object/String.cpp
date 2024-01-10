//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/String.h"

namespace hdg {
    String::String(){
        setClass("String");
    };

    String::String(std::string value): m_value(std::move(value)) {
        setClass("String");
    }

    String::String(std::string value, const Position& position):
        Object("String", position), m_value(std::move(value)){}

    String::~String() = default;

    std::string String::getValue() {
        return m_value;
    }

    Object *String::equation(Object *other) {
        if (other->getClass() == "String"){
            return new Integer(m_value == ((String*)other)->getValue());
        }
        illegalOperator();
        return nullptr;
    }

    Object *String::div(Object *other) {
        if (other->getClass() == "String"){

        }else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *String::plus(Object *other) {
        if (other->getClass() == "String"){
            std::string value = m_value + ((String*)other)->getValue();
            return new String(value, m_position);
        }else{
            illegalOperator();
            return nullptr;
        }
    }

    bool String::isTrue() {
        return !(m_value.empty());
    }

    std::string String::toString() {
        return m_value;
    }

    Object* String::copy() {
        return new String(m_value, m_position);
    }

} // hdg