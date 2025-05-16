//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_OBJECT_H
#define HDG_OBJECT_H

#include <string>
#include <vector>
#include <memory>

#include "../basic/Position.h"

namespace hdg {
    class Object; // TODO 可以从尝试创建个专门放置这种类型定义的文件，譬如叫 define.h
    typedef std::unique_ptr<Object> uObject;
    typedef std::shared_ptr<Object> sObject;
    typedef std::weak_ptr<Object>   wObject;

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
        Object(std::string className, const Position& position);
        virtual ~Object();

        void setClass(std::string className);
        std::string getClass();

        virtual Object* plus(Object* other);
        virtual Object* minus(Object* other);
        virtual Object* mul(Object* other);
        virtual Object* div(Object* other);
        virtual Object* mod(Object* other);
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

        virtual uObject plus(uObject& other);
        virtual uObject minus(uObject& other);
        virtual uObject mul(uObject& other);
        virtual uObject div(uObject& other);
        /**
         * @brief       括号运算符
         * @arg
         *      - args  参数列表。
         * */
        virtual Object* parenthesis(const std::vector<Object*>& args);
        virtual Object* brackets(const std::vector<Object*>& args);
        virtual Object* braces(const std::vector<Object*>& args);

        virtual bool isTrue();
        virtual void illegalOperator();
        virtual std::string toString() = 0;
        virtual Object* copy() = 0;
    };

} // hdg

#endif //HDG_OBJECT_H
