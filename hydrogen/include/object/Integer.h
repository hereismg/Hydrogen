//
// Created by Magnesium on 2023/7/25.
//
#pragma once

#include <memory>

#include "Object.h"
#include "List.h"

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

        sObject plus(sObject other) override;
        sObject minus(sObject other) override;
        sObject mul(sObject other) override;
        sObject div(sObject other) override;
        bool isTrue() override;

        sObject equation(sObject other) override;
        sObject notEquation(sObject other) override;
        sObject greaterThan(sObject other) override;
        sObject lessThan(sObject other) override;
        sObject greaterThanEquation(sObject other) override;
        sObject lessThanEquation(sObject other) override;


        std::string toString() override;
        sObject clone() override;
        std::string getClass() override { return "Integer"; }

//        static sList buildIntList(const std::vector<int64_t>& list);

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

