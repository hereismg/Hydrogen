//
// Created by Magnesium on 2023/7/22.
//


#ifndef HDG_RUNTIMEERROR_H
#define HDG_RUNTIMEERROR_H

#include "Error.h"
#include <utility>

namespace hdg {

    class RunTimeError: public Error{
    public:
        RunTimeError(int posStart, int posEnd, const std::string& text, std::string errorDetails);
    };

} // hdg

#endif //HDG_RUNTIMEERROR_H
