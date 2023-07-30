//
// Created by Magnesium on 2023/7/16.
//


#ifndef HDG_ILLEGALCHARERROR_H
#define HDG_ILLEGALCHARERROR_H

#include <utility>
#include "Error.h"

namespace hdg {

    class IllegalCharError: public Error{
    public:
        IllegalCharError(std::string details, const Position& position);
    };

} // hdg

#endif //HDG_ILLEGALCHARERROR_H
