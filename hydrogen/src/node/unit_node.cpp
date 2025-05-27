#include "../../include/node/unit_node.h"

#include <cassert>

#include "../../include/node/visitor.h"


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

    
    nlohmann::json new_ExeUnitNode::toJSON() const {
        nlohmann::json j{{"__class__", "ExeUnitNode"}};

        j["list"] = nlohmann::json::array();

        for (auto& n : m_list){
            j["list"].push_back(n->toJSON());
        }

        return j;
    }

    std::string new_ExeUnitNode::toString(){
        return "ExeUnitNode";
    }

    Object* new_ExeUnitNode::interpret(){
        assert(false);
    }

    void new_ExeUnitNode::accept(Visitor& visitor){
        visitor.visitExeUnitNode(*this);
    }
}