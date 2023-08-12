//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/object/Integer.h"

namespace hdg {
    Integer::Integer(long long value):
        Object("Integer"), m_value(value) {}

    Integer::Integer(long long int value, const Position &position):
        Object("Integer", position), m_value(value){}

    void Integer::setValue(long long value) {
        m_value = value;
    }

    long long Integer::getValue() const {
        return m_value;
    }

    Object *Integer::plus(Object* other) {
        if (other->getClass() == "Integer"){
            long long result = m_value + ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value + ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::minus(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value - ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value - ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::mul(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value * ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value * ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::div(Object *other) {
        if (other->getClass() == "Integer"){
            long long right = ((Integer*)other)->m_value;
            if (right == 0) throw -1;

            long long result = m_value / right;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double right = ((Float*)other)->getValue();
            if (right==0) throw -1;

            double result = m_value / right;
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
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
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::equation(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value == ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            long long result = m_value == ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::notEquation(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value != ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            long long result = m_value != ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::greaterThan(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value > ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            long long result = m_value > ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
        }
    }

    Object *Integer::lessThan(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value < ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value < ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::greaterThanEquation(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value >= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            long long result = m_value >= ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::lessThanEquation(Object *other) {
        if (other->getClass() == "Integer"){
            long long result = m_value <= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            long long result = m_value <= ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
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

} // hdg