//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/data_type/Float.h"

namespace hdg {
    Float::Float(float value):DataType(DT_FLOAT), value(value) {

    }


    Float::Float(double value): DataType(DT_FLOAT), value(value) {

    }

    double Float::getValue() const {
        return value;
    }

    DataType* Float::plus(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = value + ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = value + (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::minus(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = value - ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = value - (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::mul(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = value * ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = value * (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::div(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = value / ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = value / (double)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::pow(DataType *other) {
        if (other->typeName == DT_FLOAT){
            double result = std::pow(value, ((Float*)other)->value);
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            double result = std::pow(value, (double)((Integer*)other)->getValue());
            return new Float(result);
        }
    }

    DataType *Float::equation(DataType *other) {

        return DataType::equation(other);
    }

    DataType *Float::greaterThan(DataType *other) {
        return DataType::greaterThan(other);
    }

    DataType *Float::lessThan(DataType *other) {
        return DataType::lessThan(other);
    }

    DataType *Float::greaterThanEquation(DataType *other) {
        return DataType::greaterThanEquation(other);
    }

    DataType *Float::lessThanEquation(DataType *other) {
        return DataType::lessThanEquation(other);
    }


    std::string Float::toString() {
        std::string str = std::to_string(value);

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
        return new Float(value);
    }

} // hdg