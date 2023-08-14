//
// Created by Magnesium on 2023/7/16.
//

#ifndef HDG_ERROR_H
#define HDG_ERROR_H

#include <iostream>
#include <exception>
#include <utility>
#include <sstream>
#include "../basic/Position.h"
#include "../basic/Environment.h"

namespace hdg {

    class Error: public std::exception{
    protected:
        std::string m_name;
        std::string m_details;

        Position m_position;
        Environment* m_environment{};

    public:
        Error();
        Error(std::string name, std::string details, const Position& position);
        virtual std::string toString();
    };

} // hdg

#endif //HDG_ERROR_H
