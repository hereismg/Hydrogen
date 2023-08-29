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
#include "../error/RuntimeError.h"

namespace hdg {

    /**
     * @brief       顶级对象类。海琛语言中所有的对象都是该对象的子代。
     * @details
     * @class       这里是class
     * */

    class Object {
    protected:
        std::string m_class;        ///> 这里传入该对象实例的类名，用于强制类型转化
        Position m_position;        ///> 记录该对象定义的位置

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

        /**
         * @brief       括号运算符
         * @arg
         *      - list  参数列表。
         * */
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
