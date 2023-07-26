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

        double getValue() const;

        DataType* plus(DataType* other) override;
        DataType* minus(DataType* other) override;
        DataType* mul(DataType* other) override;
        DataType* div(DataType* other) override;
        DataType* pow(DataType* other) override;
        std::string toString() override;
    };

} // hdg

#endif //HDG_FLOAT_H
