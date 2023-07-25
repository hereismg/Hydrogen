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
        int value;

    public:
        explicit Integer(int value);

        int getValue() const;

        DataType* plus(DataType* other) override;
        DataType* minus(DataType* other) override;
        DataType* mul(DataType* other) override;
        DataType* div(DataType* other) override;
        DataType* pow(DataType* other) override;
        std::string toString() override;
    };

} // hdg

#endif //HDG_INTEGER_H
