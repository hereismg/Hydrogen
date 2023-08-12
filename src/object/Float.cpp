//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/object/Float.h"

namespace hdg {
    Float::Float(float value): Object("Float"), m_value(value) {

    }


    Float::Float(double value): Object("Float"), m_value(value) {

    }

    double Float::getValue() const {
        return m_value;
    }

    Object* Float::plus(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value + ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value + (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    Object *Float::minus(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value - ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value - (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    Object *Float::mul(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value * ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value * (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    Object *Float::div(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value / ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value / (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    Object *Float::pow(Object *other) {
        if (other->getClass() == "Float"){
            double result = std::pow(m_value, ((Float*)other)->m_value);
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = std::pow(m_value, (double)((Integer*)other)->getValue());
            return new Float(result);
        }
    }

    Object *Float::equation(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value == ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value == (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    Object* Float::notEquation(Object* other) {
        if (other->getClass() == "Float"){
            long long result = m_value != ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value != (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Float::greaterThan(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value > ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value > (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Float::lessThan(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value < ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value < (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Float::greaterThanEquation(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value >= ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value >= (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Float::lessThanEquation(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value <= ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value <= (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    Object *Float::andOperator(Object *other) {
        long long result = isTrue() && other->isTrue();
        return new Integer(result);
    }

    Object *Float::orOperator(Object *other) {
        long long result = isTrue() || other->isTrue();
        return new Integer(result);
    }

    Object *Float::notOperator() {
        long long result = !isTrue();
        return new Integer(result);
    }

    std::string Float::toString() {
        std::string str = std::to_string(m_value);

        unsigned long long i = str.length()-1;
        while(i>=0 && str[i]!='.' && str[i]=='0') i--;

        if (str[i]=='.'){
            return str.substr(0, i+2);
        }
        else{
            return str.substr(0, i+1);
        }
    }

    Object *Float::copy() {
        return new Float(m_value);
    }

    bool Float::isTrue() {
        if (m_value!=0) return true;
        else return false;
    }
} // hdg