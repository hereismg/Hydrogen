//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/error/InvalidSyntaxError.h"


namespace hdg {
    InvalidSyntaxError::InvalidSyntaxError(
            int posStart,
            int posEnd,
            const std::string &text,
            std::string errorDetails):
            Error(posStart, posEnd, text, "InvalidSyntaxError", std::move(errorDetails)){
    }
} // hdg