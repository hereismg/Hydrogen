//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/error/InvalidSyntaxError.h"


namespace hdg {
    InvalidSyntaxError::InvalidSyntaxError(std::string detail, const Position& position):
            Error("InvalidSyntaxError", std::move(detail), position){
    }
} // hdg