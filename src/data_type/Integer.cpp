//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/data_type/Integer.h"

namespace hdg {
    Integer::Integer(int value): DataType(DT_INTEGER), m_value(value) {
    }


    int Integer::getValue() const {
        return m_value;
    }

    DataType *Integer::plus(DataType* other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value + ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            double result = (double)m_value + ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Integer::minus(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value - ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            double result = (double)m_value - ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Integer::mul(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value * ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            double result = (double)m_value * ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Integer::div(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int right = ((Integer*)other)->m_value;
            if (right == 0) throw -1;

            int result = m_value / right;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            double right = ((Float*)other)->getValue();
            if (right==0) throw -1;

            double result = (double)m_value / right;
            return new Float(result);
        }
    }

    DataType *Integer::pow(DataType *other) {
        if (other->typeName == DT_INTEGER){
            double result = std::pow(m_value, ((Integer*)other)->m_value);
            return new Float(result);
        }
        else if (other->typeName == DT_FLOAT){
            double result = std::pow(m_value, ((Float*)other)->getValue());
            return new Float(result);
        }
    }

    DataType *Integer::equation(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value == ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            int result = m_value == ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Integer::notEquation(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value != ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            int result = m_value != ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Integer::greaterThan(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value > ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            int result = m_value > ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Integer::lessThan(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value < ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            int result = m_value < ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Integer::greaterThanEquation(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value >= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            int result = m_value >= ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Integer::lessThanEquation(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = m_value <= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            int result = m_value <= ((Float*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Integer::andOperator(DataType *other) {
        bool result = isTrue() && other->isTrue();
        return new Integer(result);
    }

    DataType *Integer::orOperator(DataType *other) {
        bool result = isTrue() || other->isTrue();
        return new Integer(result);
    }

    DataType *Integer::notOperator() {
        bool result = !isTrue();
        return new Integer(result);
    }

    std::string Integer::toString() {
        return std::to_string(m_value);
    }

    DataType *Integer::copy() {
        return new Integer(m_value);
    }

    bool Integer::isTrue() {
        if (m_value!=0) return true;
        else return false;
    }

} // hdg