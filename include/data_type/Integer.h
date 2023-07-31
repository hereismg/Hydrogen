//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_INTEGER_H
#define HDG_INTEGER_H

#include "DataType.h"
#include "Float.h"
#include "../error/RunTimeError.h"

namespace hdg {

    class Integer: public DataType{
    private:
        int m_value;

    public:
        explicit Integer(int value);

        int getValue() const;

        DataType* plus(DataType* other) override;
        DataType* minus(DataType* other) override;
        DataType* mul(DataType* other) override;
        DataType* div(DataType* other) override;
        DataType* pow(DataType* other) override;

        DataType* equation(DataType* other) override;
        DataType* notEquation(DataType* other) override;
        DataType* greaterThan(DataType* other) override;
        DataType* lessThan(DataType* other) override;
        DataType* greaterThanEquation(DataType* other) override;
        DataType* lessThanEquation(DataType* other) override;

        DataType* andOperator(DataType* other) override;
        DataType* orOperator(DataType* other) override;
        DataType* notOperator() override;

        bool isTrue() override;
        std::string toString() override;
        DataType* copy() override;
    };

} // hdg

#endif //HDG_INTEGER_H
