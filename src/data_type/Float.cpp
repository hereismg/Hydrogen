//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/data_type/Float.h"

namespace hdg {
    Float::Float(float value): DataType(DT_FLOAT), m_value(value) {

    }


    Float::Float(double value): DataType(DT_FLOAT), m_value(value) {

    }

    double Float::getValue() const {
        return m_value;
    }

    DataType* Float::plus(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = m_value + ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = m_value + (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::minus(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = m_value - ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = m_value - (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::mul(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = m_value * ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = m_value * (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::div(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = m_value / ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = m_value / (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::pow(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = std::pow(m_value, ((Float*)other)->m_value);
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = std::pow(m_value, (double)((Integer*)other)->getValue());
            return new Float(result);
        }
    }

    DataType *Float::equation(DataType *other) {
        if (other->typeName == DT_FLOAT){
            int result = m_value == ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_INTEGER){
            int result = m_value == (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType* Float::notEquation(DataType* other) {
        if (other->typeName == DT_FLOAT){
            int result = m_value != ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_INTEGER){
            int result = m_value != (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Float::greaterThan(DataType *other) {
        if (other->typeName == DT_FLOAT){
            int result = m_value > ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_INTEGER){
            int result = m_value > (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Float::lessThan(DataType *other) {
        if (other->typeName == DT_FLOAT){
            int result = m_value < ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_INTEGER){
            int result = m_value < (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Float::greaterThanEquation(DataType *other) {
        if (other->typeName == DT_FLOAT){
            int result = m_value >= ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_INTEGER){
            int result = m_value >= (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Float::lessThanEquation(DataType *other) {
        if (other->typeName == DT_FLOAT){
            int result = m_value <= ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->typeName == DT_INTEGER){
            int result = m_value <= (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
    }

    DataType *Float::andOperator(DataType *other) {
        int result = isTrue() && other->isTrue();
        return new Integer(result);
    }

    DataType *Float::orOperator(DataType *other) {
        int result = isTrue() || other->isTrue();
        return new Integer(result);
    }

    DataType *Float::notOperator() {
        int result = !isTrue();
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

    DataType *Float::copy() {
        return new Float(m_value);
    }

    bool Float::isTrue() {
        if (m_value!=0) return true;
        else return false;
    }
} // hdg