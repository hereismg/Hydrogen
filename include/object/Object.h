//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_OBJECT_H
#define HDG_OBJECT_H

#include <string>
#include <utility>
#include <cmath>
#include <functional>
#include "../basic/Position.h"

namespace hdg {

    class Object {
    protected:
        std::string m_class;
        Position m_position;

    public:
        Object();
        explicit Object(std::string className);
        Object(std::string className, const Position& position);

        virtual ~Object();

        std::string getClass();

        virtual Object* plus(Object* other);
        virtual Object* minus(Object* other);
        virtual Object* mul(Object* other);
        virtual Object* div(Object* other);
        virtual Object* pow(Object* other);

        virtual Object* equation(Object* other);
        virtual Object* notEquation(Object* other);
        virtual Object* greaterThan(Object* other);
        virtual Object* lessThan(Object* other);
        virtual Object* greaterThanEquation(Object* other);
        virtual Object* lessThanEquation(Object* other);

        virtual Object* andOperator(Object* other);
        virtual Object* orOperator(Object* other);
        virtual Object* notOperator();

        virtual Object* parenthesis(const std::vector<Object*>& list);
        virtual Object* brackets(Object* other);
        virtual Object* braces(const std::vector<Object*>& list);

        virtual bool isTrue();
        virtual void illegalOperator();
        virtual std::string toString() = 0;
        virtual Object* copy() = 0;
    };
} // hdg

#endif //HDG_OBJECT_H
