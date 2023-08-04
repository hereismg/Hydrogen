//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/object/Object.h"


namespace hdg {
    Object::~Object() = default;

    Object::Object(std::string typeName): typeName(std::move(typeName)) {

    }

    Object *Object::plus(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::minus(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::mul(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::div(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::pow(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::equation(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object* Object::notEquation(Object* other){
        illegalOperator();
        return nullptr;
    }

    Object *Object::greaterThan(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::lessThan(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::greaterThanEquation(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::lessThanEquation(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::andOperator(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::orOperator(Object *other) {
        illegalOperator();
        return nullptr;
    }

    Object *Object::notOperator() {
        illegalOperator();
        return nullptr;
    }

    bool Object::isTrue() {
        return false;
    }

    void Object::illegalOperator() {
        throw -2;
    }
} // hdg