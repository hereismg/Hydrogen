//
// Created by Magnesium on 2023/8/30.
//

#include "../../../include/object/function/BaseFunction.h"

namespace hdg {
    BaseFunction::BaseFunction(std::string name, const Position& position):
            Object("BaseFunction", position), m_funName(std::move(name)){}

    bool BaseFunction::checkArgs(const std::vector<Object *> &args) {
        if (m_args.size() != args.size()){
            // 参数不匹配，下面开始构建异常信息
            std::stringstream detail;
            detail << m_funName << "(): " << std::to_string(m_args.size());

            if (m_args.size()<=1) detail << " argument required, ";
            else detail << " arguments required, ";

            detail << "but " << std::to_string(args.size()) << " received.";

            // 抛出异常
            throw RuntimeError(detail.str());
        }
        return true;
    }
} // hdg