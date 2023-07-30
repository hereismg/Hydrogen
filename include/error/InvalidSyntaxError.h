//
// Created by Magnesium on 2023/7/22.
//


#ifndef HDG_INVALIDSYNTAXERROR_H
#define HDG_INVALIDSYNTAXERROR_H

#include <utility>
#include "Error.h"

namespace hdg {

    class InvalidSyntaxError: public Error{
    public:
        InvalidSyntaxError(std::string details, const Position& position);
    };

} // hdg

#endif //HDG_INVALIDSYNTAXERROR_H
