//
// Created by Magnesium on 2023/7/25.
//
#include <cmath>
#include <cassert>

#include "../../include/object/Float.h"

namespace hdg {
    Float::Float(float value): m_value(value) {
        setClass("Float");
    }


    Float::Float(double value): m_value(value) {
        setClass("Float");
    }

    Float::Float(double value, const Position &position):
        Object("Float", position), m_value(value){}

    double Float::getValue() const {
        return m_value;
    }

    Object* Float::plus(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value + ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value + (double)((Integer*)other)->getValue();
            return new Float(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::minus(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value - ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value - (double)((Integer*)other)->getValue();
            return new Float(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::mul(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value * ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value * (double)((Integer*)other)->getValue();
            return new Float(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::div(Object *other) {
        if (other->getClass() == "Float"){
            double result = m_value / ((Float*)other)->m_value;
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = m_value / (double)((Integer*)other)->getValue();
            return new Float(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::pow(Object *other) {
        if (other->getClass() == "Float"){
            double result = std::pow(m_value, ((Float*)other)->m_value);
            return new Float(result);
        }
        else if (other->getClass() == "Integer"){
            double result = std::pow(m_value, (double)((Integer*)other)->getValue());
            return new Float(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::equation(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value == ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value == (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
        else{
            assert(false);
        }
    }

    Object* Float::notEquation(Object* other) {
        if (other->getClass() == "Float"){
            long long result = m_value != ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value != (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::greaterThan(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value > ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value > (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::lessThan(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value < ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value < (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::greaterThanEquation(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value >= ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value >= (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::lessThanEquation(Object *other) {
        if (other->getClass() == "Float"){
            long long result = m_value <= ((Float*)other)->m_value;
            return new Integer(result);
        }
        else if (other->getClass() == "Integer"){
            long long result = m_value <= (double)((Integer*)other)->getValue();
            return new Integer(result);
        }
        else{
            assert(false);
        }
    }

    Object *Float::andOperator(Object *other) {
        long long result = isTrue() && other->isTrue();
        return new Integer(result);
    }

    Object *Float::orOperator(Object *other) {
        long long result = isTrue() || other->isTrue();
        return new Integer(result);
    }

    Object *Float::notOperator() {
        long long result = !isTrue();
        return new Integer(result);
    }

    std::string Float::toString() {
        std::string str = std::to_string(m_value);

        int64_t i = (int64_t)str.length()-1;
        while(i>=0 && str[i]!='.' && str[i]=='0') i--;

        if (str[i]=='.'){
            return str.substr(0, i+2);
        }
        else{
            return str.substr(0, i+1);
        }
    }

    Object *Float::copy() {
        return new Float(m_value);
    }

    bool Float::isTrue() {
        if (m_value!=0) return true;
        else return false;
    }
} // hdg