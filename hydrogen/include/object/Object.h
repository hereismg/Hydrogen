//
// Created by Magnesium on 2023/7/25.
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cassert>

#include "../basic/Position.h"
#include "../basic/Environment.h"

namespace hdg {
    class VarType;
    typedef std::weak_ptr<VarType> wVarType;

    class Visitor;
    class Object; // TODO 可以从尝试创建个专门放置这种类型定义的文件，譬如叫 define.h
    typedef std::unique_ptr<Object> uObject;
    typedef std::shared_ptr<Object> sObject;
    typedef std::weak_ptr<Object>   wObject;
    
    /**
     * @brief       顶级对象类。海琛语言中所有的对象都是该对象的子代。
     * @details
     * @class       这里是class
     * */

    class Object: public std::enable_shared_from_this<Object>{
    protected:
        std::string m_class;        ///> 这里传入该对象实例的类名，用于强制类型转化
        Position m_position;        ///> 记录该对象定义的位置

        wVarType m_type;

    public:
        Object();
        Object(std::string className, const Position& position);
        virtual ~Object();


        virtual sObject plus(sObject other);
        virtual sObject minus(sObject other);
        virtual sObject mul(sObject other);
        virtual sObject div(sObject other);
        virtual sObject mod(sObject other)  { assert(false); return nullptr; }
        virtual sObject pow(sObject other)  { assert(false); return nullptr; }
        virtual bool    isTrue();

        virtual sObject equation(sObject other) { assert(false); return nullptr; }
        virtual sObject notEquation(sObject other) { assert(false); return nullptr; }
        virtual sObject greaterThan(sObject other) { assert(false); return nullptr; }
        virtual sObject lessThan(sObject other) { assert(false); return nullptr; }
        virtual sObject greaterThanEquation(sObject other) { assert(false); return nullptr; }
        virtual sObject lessThanEquation(sObject other) { assert(false); return nullptr; }

        virtual sObject andOperator(sObject other) { assert(false); return nullptr; }
        virtual sObject orOperator(sObject other) { assert(false); return nullptr; }
        // virtual sObject notOperator();

        virtual sObject parenthesis(const std::vector<sObject>& args, Visitor& visitor); // ()
        virtual sObject brackets(const std::vector<sObject>& args, Visitor& visitor) { assert(false); return nullptr; }    // []
        virtual sObject braces(const std::vector<sObject>& args) { assert(false); return nullptr; }      // {}
        
        /**
         * 点号运算符
         * 
         * 示例：list.append(ele) 在底层通过访问此函数实现。
         */
        virtual sObject dotFun(
                const std::string& ident,
                std::vector<sObject>&& args,
                Visitor& visitor
            );

        virtual void illegalOperator();
        virtual sObject clone() { assert(false); return nullptr; }
        virtual std::string toString() { assert(false); return nullptr; }
        virtual std::string getClass() { assert(false); return nullptr; }

        // ======================================
        // 下面是弃用的方法
        // ======================================
        void setClass(std::string className);
        std::string getClass_old();

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

        /**
         * @brief       括号运算符
         * @arg
         *      - args  参数列表。
         * */
        virtual Object* parenthesis(const std::vector<Object*>& args);
        virtual Object* brackets(const std::vector<Object*>& args);
        virtual Object* braces(const std::vector<Object*>& args);

        virtual Object* copy() { assert(false); }
    };


    class VarType : public Object {
    protected:
        VarType* m_base;

        std::string m_class;
        New_Environment   m_envir;

    public:
        VarType(const char* class_)
            : m_class(class_), m_base(nullptr) {}

        VarType(const char* class_, std::map<std::string, sObject>&& table);

        New_Environment& refEnvir() { return m_envir; }
        const std::string& getClass() const { return m_class; }
    
        std::string toString() { return "VarType"; }


    };

    typedef std::shared_ptr<VarType> sVarType;
    typedef std::weak_ptr<VarType> wVarType;
} // hdg

