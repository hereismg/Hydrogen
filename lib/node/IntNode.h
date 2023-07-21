//
// Created by Magnesium on 2023/7/21.
//

#include "Node.h"

#ifndef HDG_INTNODE_H
#define HDG_INTNODE_H

namespace hdg {

    class IntNode: public Node{
    private:
        int value;

    public:
        explicit IntNode(int value);

        int getValue();
        void setValue(int value);
        std::string toString() override;
    };

} // hdg

#endif //HDG_INTNODE_H
