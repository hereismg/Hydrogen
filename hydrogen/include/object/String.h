//
// Created by Magnesium on 2023/8/4.
//

#pragma once

#include <string>

#include "List.h"
#include "Object.h"

namespace hdg {

    class String;
    typedef std::shared_ptr<String> sString;

    class String: public Object {
    protected:
        std::string m_value;

    public:
        String();
        String(std::string value);
        String(std::string value, const Position& position);
        ~String() override;

        std::string getValue() const { return m_value; };

        sObject plus(sObject other) override;
        sObject div(sObject other) override;
        sObject equation(sObject other) override;

        std::string getClass() override { return "String"; }

        static std::shared_ptr<List> buildStrList(const std::vector<std::string>& list);

        static wVarType getType();

        static sString from(sObject obj);
        static sString from(const std::string& str);
        static sString from(int64_t num);

        // ======================================
        // 下面是弃用的方法
        // ======================================

        Object* plus(Object* other) override;
        Object* div(Object* other) override;
        Object* equation(Object* other) override;
        bool isTrue() override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

