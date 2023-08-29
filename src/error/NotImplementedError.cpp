//
// Created by Magnesium on 2023/8/8.
//

#include "../../include/error/NotImplementedError.h"

namespace hdg {
    NotImplementedError::NotImplementedError() {
        m_name = "NotImplementedError";
        m_detail = "not implemented error.";
    }
} // hdg