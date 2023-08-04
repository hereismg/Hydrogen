//
// Created by Magnesium on 2023/7/25.
//


#ifndef HDG_OBJECT_H
#define HDG_OBJECT_H

#include <string>
#include <utility>
#include <cmath>

namespace hdg {
    const std::string DT_INTEGER = "Integer";
    const std::string DT_FLOAT = "FLOAT";

    class Object {
    public:
        const std::string typeName;
        explicit Object(std::string typeName);
        virtual ~Object();

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

        virtual bool isTrue();
        virtual void illegalOperator();
        virtual std::string toString() = 0;
        virtual Object* copy() = 0;
    };

} // hdg

#endif //HDG_OBJECT_H
