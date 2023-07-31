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

        virtual DataType* equation(DataType* other);
        virtual DataType* notEquation(DataType* other);
        virtual DataType* greaterThan(DataType* other);
        virtual DataType* lessThan(DataType* other);
        virtual DataType* greaterThanEquation(DataType* other);
        virtual DataType* lessThanEquation(DataType* other);

        virtual DataType* andOperator(DataType* other);
        virtual DataType* orOperator(DataType* other);
        virtual DataType* notOperator();

        virtual bool isTrue();
        virtual void illegalOperator();
        virtual std::string toString() = 0;
        virtual DataType* copy() = 0;
    };

} // hdg

#endif //HDG_DATATYPE_H
