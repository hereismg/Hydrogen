//
// Created by Magnesium on 2023/7/19.
//

#include<string>
#include"../data_type/DataType.h"

#ifndef HDG_NODE_H
#define HDG_NODE_H

namespace hdg {

    class Node {
    public:
        Node();

        virtual std::string toString();
        virtual DataType* interpret();
    };

} // hdg

#endif //HDG_NODE_H
