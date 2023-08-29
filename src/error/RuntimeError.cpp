//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/error/RuntimeError.h"

namespace hdg {
    RuntimeError::RuntimeError(): Error("RuntimeError"){}



    RuntimeError::RuntimeError(std::string details, const Position& position):
        Error("RuntimeError", std::move(details), position){}

    RuntimeError::RuntimeError(std::string name) : Error(std::move(name)) {}
} // hdg