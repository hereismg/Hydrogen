//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/data_type/DataType.h"


namespace hdg {
    DataType::~DataType() = default;

    DataType::DataType(std::string typeName):typeName(std::move(typeName)) {

    }

    DataType *DataType::plus(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::minus(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::mul(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::div(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::pow(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::equation(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::greaterThan(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::lessThan(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::greaterThanEquation(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    DataType *DataType::lessThanEquation(DataType *other) {
        illegalOperator();
        return nullptr;
    }

    void DataType::illegalOperator() {
        throw -2;
    }
} // hdg