//
// Created by Magnesium on 2023/7/16.
//


#ifndef HDG_ILLEGALCHARERROR_H
#define HDG_ILLEGALCHARERROR_H

#include "Error.h"
#include <utility>

namespace hdg {

    class IllegalCharError: public Error{
    public:
        IllegalCharError(int posStart, int posEnd, const std::string& text, std::string errorDetails);
    };

} // hdg

#endif //HDG_ILLEGALCHARERROR_H
