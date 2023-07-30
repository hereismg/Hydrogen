//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/error/RunTimeError.h"

namespace hdg {
    RunTimeError::RunTimeError(std::string details, const Position& position):
        Error("RunTimeError", std::move(details), position){

    }
} // hdg