//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_INTEGER_H
#define HDG_INTEGER_H

#include "Object.h"
#include "Float.h"
#include "../error/ZeroDivisionError.h"

namespace hdg {

    class Integer: public Object{
    private:
        long long m_value;

    public:

        explicit Integer(long long value);
        Integer(long long value, const Position& position);

        void setValue(long long value);
        [[nodiscard]] long long getValue() const;

        Object* plus(Object* other) override;
        Object* minus(Object* other) override;
        Object* mul(Object* other) override;
        Object* div(Object* other) override;
        Object* mod(Object* other) override;
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

#endif //HDG_INTEGER_H
