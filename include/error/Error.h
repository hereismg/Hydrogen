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

    class Error: public std::exception{
    protected:
        std::string m_name;
        std::string m_detail;
        std::vector<Position> m_posStack;

    public:
        Error(std::string name, const std::string& detail, const Position& position);
        void pushPosition(const Position& position);
        virtual std::string toString();
    };

} // hdg

#endif //HDG_ERROR_H
