//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/data_type/DataType.h"


namespace hdg {
    DataType::~DataType() = default;

    DataType::DataType(std::string typeName):typeName(std::move(typeName)) {

    }

    DataType *DataType::plus(DataType *other) {
        return nullptr;
    }

    DataType *DataType::minus(DataType *other) {
        return nullptr;
    }

    DataType *DataType::mul(DataType *other) {
        return nullptr;
    }

    DataType *DataType::div(DataType *other) {
        return nullptr;
    }

    DataType *DataType::pow(DataType *other) {
        return nullptr;
    }
} // hdg