//
// Created by Magnesium on 2023/7/16.
//

#ifndef HDG_ERROR_H
#define HDG_ERROR_H

#include <iostream>
#include <exception>
#include <vector>
#include <utility>
#include <sstream>
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
        explicit Error(std::string name);
        Error(std::string name, std::string detail, const Position& position);

        void setName(const std::string& name);
        void setDetail(const std::string& detail);
        std::vector<Position>* thisPosStack();

        virtual std::string toString();
    };

} // hdg

#endif //HDG_ERROR_H
