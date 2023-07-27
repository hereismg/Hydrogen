//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/error/RunTimeError.h"

namespace hdg {
    RunTimeError::RunTimeError(int posStart, int posEnd, const std::string &text, std::string errorDetails):
        Error(posStart, posEnd, text, "RunTimeError", std::move(errorDetails)){

    }
} // hdg