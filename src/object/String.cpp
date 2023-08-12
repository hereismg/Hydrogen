//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/String.h"

namespace hdg {
    String::String(): Object("String"){};

    String::String(std::string value) : Object("String"), m_value(std::move(value)) {}

    String::String(std::string value, const Position& position):
        Object("String", position), m_value(std::move(value)){}

    String::~String() = default;

    std::string String::getValue() {
        return m_value;
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
        return "\"" + m_value + "\"";
    }

    Object* String::copy() {
        return new String(m_value, m_position);
    }

} // hdg