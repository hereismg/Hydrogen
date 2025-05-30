//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_STRING_H
#define HDG_STRING_H

#include <string>

#include "List.h"
#include "Object.h"

namespace hdg {

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

        static std::shared_ptr<List> buildStrList(const std::vector<);

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

#endif //HDG_STRING_H
