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
        if (other->getClass() == "Integer"){
            int64_t result = m_value + ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value + ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::minus(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value - ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value - ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::mul(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value * ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            double result = (double)m_value * ((Float*)other)->getValue();
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::div(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t right = ((Integer*)other)->m_value;
            if (right == 0) throw ZeroDivisionError();

            int64_t result = m_value / right;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
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
        if (other->getClass() == "Integer"){
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
        if (other->getClass() == "Integer"){
            double result = std::pow(m_value, ((Integer*)other)->m_value);
            return new Float(result);
        }
        else if (other->getClass() == "Float"){
            double result = std::pow(m_value, ((Float*)other)->getValue());
            return new Float(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::equation(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value == ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int64_t result = m_value == ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::notEquation(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value != ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int64_t result = m_value != ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::greaterThan(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value > ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int64_t result = m_value > ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::lessThan(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value < ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int result = m_value < ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::greaterThanEquation(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value >= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
            int64_t result = m_value >= ((Float*)other)->getValue();
            return new Integer(result);
        }
        else{
            illegalOperator();
            return nullptr;
        }
    }

    Object *Integer::lessThanEquation(Object *other) {
        if (other->getClass() == "Integer"){
            int64_t result = m_value <= ((Integer*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Float"){
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

    sObject Integer::plus(sObject& other){
        if (typeid(*other.get()) == typeid(Integer)){
            Integer* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value + other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
        }
    }

    sObject Integer::minus(sObject& other){
        if (typeid(*other.get()) == typeid(Integer)){
            Integer* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value - other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
        }
    }

    sObject Integer::mul(sObject& other){
        if (typeid(*other.get()) == typeid(Integer)){
            Integer* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value * other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
        }
    }

    sObject Integer::div(sObject& other){
        if (typeid(*other.get()) == typeid(Integer)){
            Integer* other_int = dynamic_cast<Integer*>(other.get());
            int64_t res = m_value / other_int->getValue();

            return std::make_shared<Integer>(res);
        }
        else{
            assert(false && "Error!");
        }
    }

    sInteger Integer::True  = std::make_shared<Integer>(1);
    sInteger Integer::False = std::make_shared<Integer>(0);

    sObject Integer::equation(sObject& other) {
        if (typeid(*other.get()) != typeid(Integer)) return Integer::False;

        auto otherVal = dynamic_cast<Integer*>(other.get())->getValue();

        if (otherVal != m_value) return Integer::False;

        return Integer::True;
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


} // hdg