//
// Created by Magnesium on 2023/8/29.
//

#ifndef HDG_ZERODIVISIONERROR_H
#define HDG_ZERODIVISIONERROR_H

#include "RuntimeError.h"

namespace hdg {

    class ZeroDivisionError: public RuntimeError{
    public:
        ZeroDivisionError();
    };

} // hdg

#endif //HDG_ZERODIVISIONERROR_H
