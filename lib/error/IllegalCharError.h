//
// Created by Magnesium on 2023/7/16.
//

#include "Error.h"
#include <utility>

#ifndef HDG_ILLEGALCHARERROR_H
#define HDG_ILLEGALCHARERROR_H

namespace hdg {

    class IllegalCharError: public Error{
    public:
        IllegalCharError(int posStart, int posEnd, std::string errorDetails);
    };

} // hdg

#endif //HDG_ILLEGALCHARERROR_H
