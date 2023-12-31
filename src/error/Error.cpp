//
// Created by Magnesium on 2023/7/16.
//

#include <ranges>

#include "../../include/error/Error.h"

namespace hdg {
    Error::Error() = default;

    Error::Error(std::string name): m_name(std::move(name)){}

    Error::Error(std::string name, std::string detail):
    m_name(std::move(name)), m_detail(std::move(detail)) {}

    Error::Error(std::string name, std::string detail, const Position& position):
        m_name(std::move(name)), m_detail(std::move(detail)){
        m_posStack.emplace_back(position);
    }


    void Error::setName(const std::string& name) {
        m_name = name;
    }

    void Error::setDetail(const std::string& detail) {
        m_detail = detail;
    }

    std::vector<Position>* Error::thisPosStack(){
        return &m_posStack;
    }

    std::string Error::toString() {
        std::stringstream information;
        for (auto & iter : std::ranges::reverse_view(m_posStack))
            information << iter.toString() << std::endl;

        information << m_name << ": " << m_detail << std::endl;
        return information.str();
    }


} // hdg