//
// Created by Magnesium on 2023/7/22.
//


#ifndef HDG_RUNTIMEERROR_H
#define HDG_RUNTIMEERROR_H

#include <utility>
#include "Error.h"

namespace hdg {

    class RuntimeError: public Error{
    public:
        RuntimeError(std::string details, const Position& position);
    };

} // hdg

#endif //HDG_RUNTIMEERROR_H
