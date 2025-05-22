//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_INTEGER_H
#define HDG_INTEGER_H

#include "Object.h"

namespace hdg {
    class Integer;
    typedef std::unique_ptr<Integer> uInteger;
    typedef std::shared_ptr<Integer> sInteger;
    typedef std::weak_ptr<Integer>   wInteger;

    class Integer: public Object{
    private:
        int64_t m_value;

    public:

        explicit Integer(int64_t value);
        Integer(int64_t value, const Position& position);

        void setValue(int64_t value);
        [[nodiscard]] int64_t getValue() const;

        sObject plus(sObject& other) override;
        sObject minus(sObject& other) override;
        sObject mul(sObject& other) override;
        sObject div(sObject& other) override;
        bool isTrue() override;

        sObject equation(sObject& other) override;

        std::string toString() override;
        sObject clone() override;

        // static sInteger False() { return std::make_shared<Integer>(0); }
        // static sInteger True() { return std::make_shared<Integer>(1); }

        static sInteger False;
        static sInteger True;

        // ======================================
        // 下面是弃用的方法
        // ======================================

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
        Object* copy() override;
    };

} // hdg

#endif //HDG_INTEGER_H
