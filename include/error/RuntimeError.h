//
// Created by Magnesium on 2023/7/22.
//


#ifndef HDG_RUNTIMEERROR_H
#define HDG_RUNTIMEERROR_H

#include <utility>
#include "Error.h"

namespace hdg {

    /**
     * @brief       运行时异常
     * @details
     * */

    class RuntimeError: public Error{
    public:
        RuntimeError();
        explicit RuntimeError(std::string detail);
        RuntimeError(std::string detail, const Position& position);

    protected:
        RuntimeError(std::string name, std::string detail, const Position& position);
    };

} // hdg

#endif //HDG_RUNTIMEERROR_H
