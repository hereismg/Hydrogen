//
// Created by Magnesium on 2023/7/16.
//

#include <utility>

#include "../../include/error/IllegalCharError.h"


namespace hdg {
    IllegalCharError::IllegalCharError(std::string details, const Position& position):
        Error("IllegalCharError", std::move(details), position){

    }
} // hdg