//
// Created by Magnesium on 2023/7/16.
//

#include <utility>

#include "../../include/error/Error.h"

namespace hdg {
    Error::Error(std::string name, const std::string& detail, const Position& position):
        m_name(std::move(name)), m_detail(detail){
        m_posStack.emplace_back(position);
    }

    void Error::pushPosition(const Position &position) {
        m_posStack.emplace_back(position);
    }

    std::string Error::toString() {
        std::stringstream information;
        information << m_name << ": " << m_detail << std::endl << std::endl;
        information << m_posStack[0].toString();
        return information.str();
    }
} // hdg