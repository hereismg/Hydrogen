//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_NUMBERNODE_H
#define HDG_NUMBERNODE_H

#include "ObjectNode.h"
#include "../object/Integer.h"
#include "../object/Float.h"

namespace hdg {

    class NumberNode: public Node{
    protected:
        Object* m_value;

    public:
        NumberNode(int value, const Position& position);
        NumberNode(float value, const Position& position);
        NumberNode(double value, const Position& position);
        ~NumberNode() override;

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_NUMBERNODE_H
