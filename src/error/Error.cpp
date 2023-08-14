//
// Created by Magnesium on 2023/7/16.
//

#include <utility>

#include "../../include/error/Error.h"

namespace hdg {
    Error::Error() = default;

    Error::Error(std::string name, std::string details, const Position& position):
        m_name(std::move(name)), m_details(std::move(details)), m_position(position){
    }

    std::string Error::toString() {
        std::stringstream information;
        information << m_name << ": " << m_details << std::endl << std::endl;
        information << m_position.arrow();
        return information.str();
    }
} // hdg