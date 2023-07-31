//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/data_type/Integer.h"

namespace hdg {
    Integer::Integer(int value): DataType(DT_INTEGER), value(value) {
    }


    int Integer::getValue() const {
        return value;
    }

    DataType *Integer::plus(DataType* other) {
        if (other->typeName == DT_INTEGER){
            int result = value + ((Integer*)other)->value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            float result = (float)value + ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Integer::minus(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = value - ((Integer*)other)->value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            float result = (float)value - ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Integer::mul(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int result = value * ((Integer*)other)->value;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            float result = (float)value * ((Float*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Integer::div(DataType *other) {
        if (other->typeName == DT_INTEGER){
            int right = ((Integer*)other)->value;
            if (right == 0) throw -1;

            int result = value / right;
            return new Integer(result);
        }
        else if (other->typeName == DT_FLOAT){
            float right = ((Float*)other)->getValue();
            if (right==0) throw -1;

            float result = (float)value / right;
            return new Float(result);
        }
    }

    DataType *Integer::pow(DataType *other) {
        if (other->typeName == DT_INTEGER){
            float result = std::pow(value, ((Integer*)other)->value);
            return new Float(result);
        }
        else if (other->typeName == DT_FLOAT){
            float result = std::pow(value, ((Float*)other)->getValue());
            return new Float(result);
        }
    }

    std::string Integer::toString() {
        return std::to_string(value);
    }

    DataType *Integer::copy() {
        return new Integer(value);
    }
} // hdg