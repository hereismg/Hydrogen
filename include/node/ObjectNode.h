//
// Created by Magnesium on 2023/8/9.
//

#ifndef HDG_OBJECTNODE_H
#define HDG_OBJECTNODE_H

#include "Node.h"

namespace hdg {

    class ObjectNode: public Node{
    public:
        ObjectNode();
        ~ObjectNode() override;

        virtual std::string toString() = 0;
        virtual Object* interpret() = 0;
    };

} // hdg

#endif //HDG_OBJECTNODE_H
