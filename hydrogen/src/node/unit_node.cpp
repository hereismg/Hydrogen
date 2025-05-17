#include "../../include/node/unit_node.h"

#include <cassert>

namespace hdg{
    new_ExeUnitNode::new_ExeUnitNode(std::vector<uNode>&& list)
        : m_list(std::move(list))
    {}

    new_ExeUnitNode::new_ExeUnitNode(std::vector<uNode>&& list, const Position& pos)
        : Node(pos), m_list(std::move(list))
    {}

    std::vector<uNode>& new_ExeUnitNode::getList(){
        return m_list;
    }
}