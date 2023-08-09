//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/object/Integer.h"

namespace hdg {
    Integer::Integer(int value): Object("Integer"), m_value(value) {
    }

    int Integer::getValue() const {
        return m_value;
    }

    Object *Integer::plus(Object* other) {
        if (other->getClass() == "Integer"){
            int result = m_value + ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value + ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    Object *Integer::minus(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value - ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value - ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    Object *Integer::mul(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value * ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value * ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    Object *Integer::div(Object *other) {
        if (other->getClass() == "Integer"){
            int right = ((Integer*)other)->m_value;
            if (right == 0) throw -1;

            int result = m_value / right;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double right = ((Float*)other)->getValue();
            if (right==0) throw -1;

            double result = (double)m_value / right;
            return new Float(result);
        }
    }

    Object *Integer::pow(Object *other) {
        if (other->getClass() == "Integer"){
            double result = std::pow(m_value, ((Integer*)other)->m_value);
            return new Float(result);
        }
        else if (other->getClass() == "Float"){
            double result = std::pow(m_value, ((Float*)other)->getValue());
            return new Float(result);
        }
    }

    Object *Integer::equation(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value == ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value == ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Integer::notEquation(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value != ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value != ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Integer::greaterThan(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value > ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value > ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
        }
    }

    Object *Integer::lessThan(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value < ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value < ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Integer::greaterThanEquation(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value >= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value >= ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Integer::lessThanEquation(Object *other) {
        if (other->getClass() == "Integer"){
            int result = m_value <= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value <= ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Integer::andOperator(Object *other) {
        bool result = isTrue() && other->isTrue();
        return new Integer(result);
    }

    Object *Integer::orOperator(Object *other) {
        bool result = isTrue() || other->isTrue();
        return new Integer(result);
    }

    Object *Integer::notOperator() {
        bool result = !isTrue();
        return new Integer(result);
    }

    std::string Integer::toString() {
        return std::to_string(m_value);
    }

    Object *Integer::copy() {
        return new Integer(m_value);
    }

    bool Integer::isTrue() {
        if (m_value!=0) return true;
        else return false;
    }

    void Integer::setValue(int value) {
        m_value = value;
    }

} // hdg