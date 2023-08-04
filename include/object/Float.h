//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_FLOAT_H
#define HDG_FLOAT_H

#include <iostream>
#include "Object.h"
#include "Integer.h"

namespace hdg {

    class Float: public Object {
    private:
        double m_value;

    public:
        explicit Float(float value);
        explicit Float(double value);

        [[nodiscard]] double getValue() const;

        Object* plus(Object* other) override;
        Object* minus(Object* other) override;
        Object* mul(Object* other) override;
        Object* div(Object* other) override;
        Object* pow(Object* other) override;

        Object* equation(Object* other) override;
        Object* notEquation(Object* other) override;
        Object* greaterThan(Object* other) override;
        Object* lessThan(Object* other) override;
        Object* greaterThanEquation(Object* other) override;
        Object* lessThanEquation(Object* other) override;

        Object* andOperator(Object* other) override;
        Object* orOperator(Object* other) override;
        Object* notOperator() override;

        bool isTrue() override;
        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_FLOAT_H
