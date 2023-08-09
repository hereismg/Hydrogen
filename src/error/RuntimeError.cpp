//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/error/RuntimeError.h"

namespace hdg {
    RuntimeError::RuntimeError(std::string details, const Position& position):
        Error("RuntimeError", std::move(details), position){

    }
} // hdg