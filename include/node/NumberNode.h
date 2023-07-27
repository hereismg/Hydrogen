//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_NUMBERNODE_H
#define HDG_NUMBERNODE_H

#include "Node.h"
#include "../data_type/Integer.h"
#include "../data_type/Float.h"

namespace hdg {

    class NumberNode: public Node{
    private:
        DataType* m_value;

    public:
        NumberNode(int value, const Position& position);
        NumberNode(float value, const Position& position);
        NumberNode(double value, const Position& position);
        ~NumberNode();

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_NUMBERNODE_H
