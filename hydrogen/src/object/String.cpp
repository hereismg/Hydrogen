//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/String.h"

#include "../../include/object/Integer.h"

namespace hdg {
    String::String(){
        setClass("String");
    };

    String::String(std::string value): m_value(std::move(value)) {
        setClass("String");
    }

    String::String(std::string value, const Position& position):
        Object("String", position), m_value(std::move(value)){}

    String::~String() = default;

    sObject String::plus(sObject other)
    {
        assert(other != nullptr);

        if (typeid(*other.get()) == typeid(String))
        {
            auto otherStr = dynamic_cast<String*>(other.get());

            return std::make_shared<String>(m_value + otherStr->getValue());
        }
        else
        {
            assert(false);
            return nullptr;
        }
    }

    sObject String::div(sObject other)
    {
        assert(other != nullptr);

        if (typeid(*other.get()) == typeid(String))
        {
            auto otherStr = dynamic_cast<String*>(other.get());
            std::string ori = m_value, sql = otherStr->getValue();

            std::vector<sObject> strList;
            int64_t end = ori.find(sql);
            while (end != -1)
            {
                std::string temp = ori.substr(0, end);
                if (temp != "") strList.push_back(std::make_shared<String>(temp));
                ori.erase(ori.begin(), ori.begin() + (int)end + 1);
                end = ori.find(sql);
            }
            std::string temp = ori.substr(0, end);
            if (temp != "") strList.push_back(std::make_shared<String>(ori.substr(0, end)));
            return std::make_shared<List>(std::move(strList));
        }
        else
        {
            assert(false);
            return nullptr;
        }
    }

    sObject String::equation(sObject other) {
        assert(other != nullptr);

        auto other_str = String::from(other);

        if (other_str->m_value == this->m_value) return Integer::True;
        else return Integer::False;

        // if (typeid(*other.get()) == typeid(String))
        // {
        //     String* otherStr = dynamic_cast<String*>(other.get());

        //     if (otherStr->getValue() == m_value) return Integer::True;
        //     else return Integer::False;
        // }
        // else
        // {
        //     assert(false);
        //     return nullptr;
        // }
    }


    Object *String::equation(Object *other) {
        if (other->getClass_old() == "String"){
            return new Integer(m_value == ((String*)other)->getValue());
        }
        illegalOperator();
        return nullptr;
    }

    Object *String::div(Object *other) {
        if (other->getClass_old() == "String"){
            std::vector<Object*> result;
            std::string ori = m_value, spl = ((String*)other)->getValue();
            int64_t end = ori.find(spl);
            while (end != -1) {
                result.push_back(new String(ori.substr(0, end)));
                ori.erase(ori.begin(), ori.begin() + (int)end + 1);
                end = ori.find(spl);
            }
            result.push_back(new String(ori.substr(0, end)));
            return new List(result);
        }else{
            illegalOperator();
            return nullptr;
        }
    }

    std::shared_ptr<List> String::buildStrList(const std::vector<std::string>& list){
        auto res = std::make_shared<List>();
        for (auto& i : list){
            res->getList().push_back(std::make_shared<String>(i));
        }
        return res;
    }

    wVarType String::getType() {
        static auto strType = [] {
            auto type = std::make_shared<VarType>("String");
            
            auto envir = type->refEnvir();

            envir.setSymbol("len", std::make_shared<Integer>(2025));

            return type;
        }();
        
        return strType;
    }

    sString String::from(const sObject& obj) {
        assert(obj != nullptr);
        assert(typeid(*obj.get()) == typeid(String));

        return std::dynamic_pointer_cast<String>(obj);
    }

    sString String::from(const std::string& str) {
        return std::make_shared<String>(str);
    }

    sString String::from(int64_t num) {
        return std::make_shared<String>(std::to_string(num));
    }


    Object *String::plus(Object *other) {
        if (other->getClass_old() == "String"){
            std::string value = m_value + ((String*)other)->getValue();
            return new String(value, m_position);
        }else{
            illegalOperator();
            return nullptr;
        }
    }

    bool String::isTrue() {
        return !(m_value.empty());
    }

    std::string String::toString() {
        return m_value;
    }

    Object* String::copy() {
        return new String(m_value, m_position);
    }

} // hdg