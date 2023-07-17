//
// Created by Magnesium on 2023/7/16.
//

#include "IllegalCharError.h"


namespace hdg {
    IllegalCharError::IllegalCharError(int posStart, int posEnd, std::string errorDetails):
        Error(posStart, posEnd, "IllegalCharError", std::move(errorDetails)){

    }
} // hdg