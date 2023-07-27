//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_DATATYPE_H
#define HDG_DATATYPE_H

#include <string>
#include <utility>
#include <cmath>

namespace hdg {
    const std::string DT_INTEGER = "Integer";
    const std::string DT_FLOAT = "FLOAT";

    class DataType {
    public:
        const std::string typeName;
        explicit DataType(std::string typeName);
        virtual ~DataType();

        virtual DataType* plus(DataType* other);
        virtual DataType* minus(DataType* other);
        virtual DataType* mul(DataType* other);
        virtual DataType* div(DataType* other);
        virtual DataType* pow(DataType* other);
        virtual std::string toString() = 0;
    };

} // hdg

#endif //HDG_DATATYPE_H
