//
// Created by Magnesium on 2023/7/25.
//

#include "Float.h"

namespace hdg {
    Float::Float(float value):DataType(DT_FLOAT), value(value) {

    }


    Float::Float(double value): DataType(DT_FLOAT), value(value) {

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

} // hdg