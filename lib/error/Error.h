//
// Created by Magnesium on 2023/7/16.
//

#include <iostream>
#include <exception>
#include <utility>

#ifndef HDG_ERROR_H
#define HDG_ERROR_H

namespace hdg {

    std::string buildArrow(const std::string& text, int posStart, int posEnd);

    class Error: public std::exception{
    public:
        int posStart;
        int posEnd;
        const std::string& text;
        std::string errorName;
        std::string errorDetails;

        Error(int posStart, int posEnd, const std::string& text, std::string errorName, std::string errorDetails);

        friend std::ostream& operator<<(std::ostream& out, Error& error);
    };

} // hdg

#endif //HDG_ERROR_H
