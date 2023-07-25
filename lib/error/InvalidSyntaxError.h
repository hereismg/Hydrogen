//
// Created by Magnesium on 2023/7/22.
//


#ifndef HDG_INVALIDSYNTAXERROR_H
#define HDG_INVALIDSYNTAXERROR_H

#include "Error.h"
#include <utility>

namespace hdg {

    class InvalidSyntaxError: public Error{
    public:
        InvalidSyntaxError(int posStart, int posEnd, const std::string& text, std::string errorDetails);
    };

} // hdg

#endif //HDG_INVALIDSYNTAXERROR_H
