//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/error/RuntimeError.h"

namespace hdg {
    RuntimeError::RuntimeError(): Error("RuntimeError"){}

    RuntimeError::RuntimeError(std::string detail):
    Error("RuntimeError", std::move(detail)) {}

    RuntimeError::RuntimeError(std::string details, const Position& position):
        Error("RuntimeError", std::move(details), position){}

    RuntimeError::RuntimeError(std::string name, std::string detail, const Position &position) :
        Error(std::move(name), std::move(detail), position) {}
} // hdg