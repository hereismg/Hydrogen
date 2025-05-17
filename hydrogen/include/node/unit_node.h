#ifndef UNIT_NODE_H
#define UNIT_NODE_H

#include "Node.h"

namespace hdg{
    class new_ExeUnitNode:public Node{
    protected:
        std::vector<uNode> m_list;

    public:
        new_ExeUnitNode() = default;
        new_ExeUnitNode(std::vector<uNode>&& list);
        new_ExeUnitNode(std::vector<uNode>&& list, const Position& pos);
        
        ~new_ExeUnitNode() = default;

        new_ExeUnitNode(const new_ExeUnitNode&) = delete;
        new_ExeUnitNode& operator=(const new_ExeUnitNode&) = delete;
        
        new_ExeUnitNode(new_ExeUnitNode&&) noexcept = default;
        new_ExeUnitNode& operator=(new_ExeUnitNode&&) noexcept = default;

        std::vector<uNode>& getList();
    };
}

#endif