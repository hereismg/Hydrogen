//
// Created by Magnesium on 2023/8/2.
//

#ifndef HDG_NONE_H
#define HDG_NONE_H

#include "DataType.h"
#include "Integer.h"

namespace hdg {

    class None: public DataType{
    public:
        None();

        DataType* notOperator() override;

        std::string toString() override;
        DataType* copy() override;
    };

} // hdg

#endif //HDG_NONE_H
