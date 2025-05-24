//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_LIST_H
#define HDG_LIST_H

#include "Object.h"

namespace hdg {
    class List;
    typedef std::unique_ptr<List> uList;
    typedef std::shared_ptr<List> sList;
    typedef std::weak_ptr<List>   wList;

    class List: public Object{
    protected:
        std::vector<sObject> m_list;

    public:
        List();
        List(std::vector<sObject>&& list);
        List(size_t count, sObject obj);

        List(const List&) = delete;

        sObject plus(sObject other) override;

        sObject equation(sObject other) override;

        sObject brackets(const std::vector<sObject>& args, Visitor& visitor) override;    // []

        bool isTrue() override;
        std::vector<sObject>& getList() { return m_list; }

        std::string toString() override;
        sObject clone() override;
        std::string getClass() override { return "List"; }

    // ======================================
    // 下面是弃用的方法
    // ======================================
    private:
        std::vector<Object*> m_list_old;

    public:
        explicit List(const std::vector<Object*>& list);
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

        std::vector<Object*> getValue();
        Object* brackets(const std::vector<Object*>& args) override;

        Object* copy() override;
    };

} // hdg

#endif //HDG_LIST_H
