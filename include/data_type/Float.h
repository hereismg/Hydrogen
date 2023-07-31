//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_FLOAT_H
#define HDG_FLOAT_H

#include "DataType.h"
#include "Integer.h"
#include <iostream>

namespace hdg {

    class Float: public DataType {
    private:
        double value;

    public:
        explicit Float(float value);
        explicit Float(double value);

        [[nodiscard]] double getValue() const;

        DataType* plus(DataType* other) override;
        DataType* minus(DataType* other) override;
        DataType* mul(DataType* other) override;
        DataType* div(DataType* other) override;
        DataType* pow(DataType* other) override;

        DataType* equation(DataType* other) override;
        DataType* greaterThan(DataType* other) override;
        DataType* lessThan(DataType* other) override;
        DataType* greaterThanEquation(DataType* other) override;
        DataType* lessThanEquation(DataType* other) override;

        std::string toString() override;
        DataType* copy() override;
    };

} // hdg

#endif //HDG_FLOAT_H
