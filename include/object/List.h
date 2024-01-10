//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_LIST_H
#define HDG_LIST_H

#include "Object.h"
#include "Integer.h"
#include <vector>
#include <sstream>

namespace hdg {

    class List: public Object{
    private:
        std::vector<Object*> m_list;

    public:
        List();
        explicit List(const std::vector<Object*>& list);

        std::vector<Object*> getValue();

        Object* plus(Object* other) override;
//        Object* minus(Object* other) override;
//        Object* mul(Object* other) override;
//        Object* div(Object* other) override;
//        Object* mod(Object* other) override;
//        Object* pow(Object* other) override;

        Object* equation(Object* other) override;
//        Object* notEquation(Object* other) override;
//        Object* greaterThan(Object* other) override;
//        Object* lessThan(Object* other) override;
//        Object* greaterThanEquation(Object* other) override;
//        Object* lessThanEquation(Object* other) override;

//        Object* andOperator(Object* other) override;
//        Object* orOperator(Object* other) override;
//        Object* notOperator() override;

        Object* brackets(const std::vector<Object*>& args) override;

        bool isTrue() override;
        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_LIST_H
