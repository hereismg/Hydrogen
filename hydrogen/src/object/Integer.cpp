//
// Created by Magnesium on 2023/7/25.
//
#include "../../include/object/Integer.h"

#include <cmath>
#include <cassert>

#include "../../include/object/Float.h"
#include "../../include/basic/Error.h"

namespace hdg {
    Integer::Integer(int64_t value): m_value(value) {
        setClass("Integer");
    }

    Integer::Integer(int64_t value, const Position &position):
        Object("Integer", position), m_value(value){}

    void Integer::setValue(int64_t value) {
        m_value = value;
    }

    int64_t Integer::getValue() const {
        return m_value;
    }

    Object *Integer::plus(Object* other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value + ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            double result = (double)m_value + ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::minus(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value - ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            double result = (double)m_value - ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::mul(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value * ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            double result = (double)m_value * ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::div(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t right = ((Integer*)other)->m_value;
            if (right == 0) throw ZeroDivisionError();

            int64_t result = m_value / right;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            double right = ((Float*)other)->getValue();
            if (right == 0) throw ZeroDivisionError();

            double result = m_value / right;
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::mod(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t right = ((Integer*)other)->m_value;
            if (right == 0) throw ZeroDivisionError();

            int64_t result = m_value % right;
            return new Integer(result);
        }
        else {
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::pow(Object *other) {
        if (other->getClass_old() == "Integer"){
            double result = std::pow(m_value, ((Integer*)other)->m_value);
            return new Float(result);
        }
        else if (other->getClass_old() == "Float"){
            double result = std::pow(m_value, ((Float*)other)->getValue());
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::equation(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value == ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            int64_t result = m_value == ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::notEquation(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value != ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            int64_t result = m_value != ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::greaterThan(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value > ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            int64_t result = m_value > ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::lessThan(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value < ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            int result = m_value < ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::greaterThanEquation(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value >= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            int64_t result = m_value >= ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::lessThanEquation(Object *other) {
        if (other->getClass_old() == "Integer"){
            int64_t result = m_value <= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass_old() == "Float"){
            int64_t result = m_value <= ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::andOperator(Object *other) {
        bool result = isTrue() && other->isTrue();
        return new Integer(result);
    }

    Object *Integer::orOperator(Object *other) {
        bool result = isTrue() || other->isTrue();
        return new Integer(result);
    }

    Object *Integer::notOperator() {
        bool result = !isTrue();
        return new Integer(result);
    }

    sObject Integer::plus(sObject other){
        assert(other.get() != nullptr);
        if (typeid(*other.get()) == typeid(Integer)){
            Integer* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value + other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
            return nullptr;
        }
    }

    sObject Integer::minus(sObject other){
        assert(other.get() != nullptr);
        if (typeid(*other.get()) == typeid(Integer)){
            auto* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value - other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
            return nullptr;
        }
    }

    sObject Integer::mul(sObject other){
        assert(other.get() != nullptr);
        if (typeid(*other.get()) == typeid(Integer)){
            auto* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value * other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
            return nullptr;
        }
    }

    sObject Integer::div(sObject other){
        assert(other.get() != nullptr);
        if (typeid(*other.get()) == typeid(Integer)){
            auto* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value / other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
            return nullptr;
        }
    }

    sInteger Integer::True  = std::make_shared<Integer>(1);
    sInteger Integer::False = std::make_shared<Integer>(0);

    sObject Integer::equation(sObject other) {
        assert(other.get() != nullptr);
        if (typeid(*other.get()) != typeid(Integer)) return Integer::False;

        auto otherVal = dynamic_cast<Integer*>(other.get())->getValue();

        return std::make_shared<Integer>(m_value == otherVal);
    }

    sObject Integer::notEquation(sObject other) {
        assert(other.get() != nullptr);
        if (typeid(*other.get()) != typeid(Integer)) return Integer::False;

        auto otherVal = dynamic_cast<Integer*>(other.get())->getValue();

        return std::make_shared<Integer>(m_value != otherVal);
    }

    sObject Integer::greaterThan(sObject other) {
        assert(other.get() != nullptr);
        if (typeid(*other.get()) != typeid(Integer)) return Integer::False;

        auto otherVal = dynamic_cast<Integer*>(other.get())->getValue();

        return std::make_shared<Integer>(m_value > otherVal);
    }

    sObject Integer::lessThan(sObject other) {
        assert(other.get() != nullptr);
        if (typeid(*other.get()) != typeid(Integer)) return Integer::False;

        auto otherVal = dynamic_cast<Integer*>(other.get())->getValue();

        return std::make_shared<Integer>(m_value < otherVal);
    }

    sObject Integer::greaterThanEquation(sObject other) {
        assert(other.get() != nullptr);
        if (typeid(*other.get()) != typeid(Integer)) return Integer::False;

        auto otherVal = dynamic_cast<Integer*>(other.get())->getValue();

        return std::make_shared<Integer>(m_value >= otherVal);
    }

    sObject Integer::lessThanEquation(sObject other) {
        assert(other.get() != nullptr);
        if (typeid(*other.get()) != typeid(Integer)) return Integer::False;

        auto otherVal = dynamic_cast<Integer*>(other.get())->getValue();

        return std::make_shared<Integer>(m_value <= otherVal);
    }

    sInteger Integer::from(const sObject& obj) {
        assert(obj != nullptr);
        assert(typeid(*obj.get()) == typeid(Integer));

        return std::dynamic_pointer_cast<Integer>(obj);
    }

    sInteger Integer::from(int64_t num) {
        return std::make_shared<Integer>(num);
    }

    std::string Integer::toString() {
        return std::to_string(m_value);
    }

    Object *Integer::copy() {
        return new Integer(m_value);
    }

    bool Integer::isTrue() {
        if (m_value!=0) return true;
        else return false;
    }

    sObject Integer::clone() {
        return std::make_shared<Integer>(m_value);
    }

//    sList Integer::buildIntList(const std::vector<int64_t> &list) {
//        auto res = std::make_shared<List>();
//        for (auto& i : list) {
//            res->getList().push_back(std::make_shared<Integer>(i));
//        }
//        return res;
//    }


} // hdg