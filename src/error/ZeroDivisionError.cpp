//
// Created by Magnesium on 2023/8/29.
//

#include "../../include/error/ZeroDivisionError.h"

namespace hdg {
    ZeroDivisionError::ZeroDivisionError() {
        m_name = "ZeroDivisionError";
        m_detail = "Integer division or modulo by zero.";
    }
} // hdg