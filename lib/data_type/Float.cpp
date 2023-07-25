//
// Created by Magnesium on 2023/7/25.
//

#include "Float.h"

namespace hdg {
    Float::Float(float value):DataType(DT_FLOAT), value(value) {

    }

    std::string Float::toString() {
        return std::to_string(value);
    }

    float Float::getValue() {
        return value;
    }

    DataType* Float::plus(DataType *other) {
        if (other->typeName == DT_FLOAT){
            float result = value + ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            float result = value + (float)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::minus(DataType *other) {
        if (other->typeName == DT_FLOAT){
            float result = value - ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            float result = value - (float)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::mul(DataType *other) {
        if (other->typeName == DT_FLOAT){
            float result = value * ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            float result = value * (float)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::div(DataType *other) {
        if (other->typeName == DT_FLOAT){
            float result = value / ((Float*)other)->value;
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            float result = value / (float)((Integer*)other)->getValue();
            return new Float(result);
        }
    }

    DataType *Float::pow(DataType *other) {
        if (other->typeName == DT_FLOAT){
            float result = std::pow(value, ((Float*)other)->value);
            return new Float(result);
        }
        else if (other->typeName == DT_INTEGER){
            float result = std::pow(value, (float)((Integer*)other)->getValue());
            return new Float(result);
        }
    }
} // hdg