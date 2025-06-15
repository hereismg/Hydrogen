//
// Created by Magnesium on 2023/7/16.
//

#pragma once

#include <iostream>
#include <exception>
#include <vector>
#include <utility>
#include <sstream>
#include <ranges>
#include "../basic/Position.h"

namespace hdg {

    /**
     * @brief 异常顶级类
     * */
    class Error: public std::exception{
    protected:
        std::string m_name;                 ///> 异常的名字
        std::string m_detail;               ///> 异常的信息
        std::vector<Position> m_posStack;   ///> 异常标记栈。该栈回存放全部的异常位置

    public:
        Error();
        explicit Error(std::string detail);
        Error(std::string name, std::string detail);
        Error(std::string name, std::string detail, const Position& position);

        void setName(const std::string& name);
        void setDetail(const std::string& detail);
        std::vector<Position>* thisPosStack();

        virtual std::string toString();
    };

    class IllegalCharError: public Error{
    public:
        IllegalCharError(std::string details, const Position& position);
    };

    class InvalidSyntaxError: public Error{
    public:
        InvalidSyntaxError(std::string details, const Position& position);
    };

    /**
     * @brief       运行时异常
     * @details
     * */

    class RuntimeError: public Error{
    public:
        RuntimeError();
        explicit RuntimeError(std::string detail);
        RuntimeError(std::string detail, const Position& position);

    protected:
        RuntimeError(std::string name, std::string detail, const Position& position);
    };


    class NotImplementedError: public RuntimeError{
    public:
        NotImplementedError();
    };

    class ZeroDivisionError: public RuntimeError{
    public:
        ZeroDivisionError();
    };

} // hdg

