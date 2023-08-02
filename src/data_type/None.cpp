//
// Created by Magnesium on 2023/8/2.
//

#include "../../include/data_type/None.h"

namespace hdg {
    None::None():
        DataType("None"){

    }

    std::string None::toString() {
        return "None";
    }

    DataType *None::copy() {
        return new None();
    }

    DataType *None::notOperator() {
        return new Integer(1);
    }
} // hdg