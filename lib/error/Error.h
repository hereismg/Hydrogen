//
// Created by Magnesium on 2023/7/16.
//

#include<iostream>
#include<exception>

#ifndef HDG_ERROR_H
#define HDG_ERROR_H

namespace hdg {

    class Error: public std::exception{
    public:
        int posStart;
        int posEnd;
        std::string errorName;
        std::string errorDetails;

        Error(int posStart, int posEnd, std::string errorName, std::string errorDetails);

        friend std::ostream& operator<<(std::ostream& out, Error& error);
    };

} // hdg

#endif //HDG_ERROR_H
