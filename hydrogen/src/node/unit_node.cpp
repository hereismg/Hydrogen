#include "../../include/node/unit_node.h"

#include <cassert>

#include "../../include/node/visitor.h"


namespace hdg{
    ExeUnitNode::ExeUnitNode(std::vector<uNode> list)
        : m_list(move(list))
    {}

    ExeUnitNode::ExeUnitNode(std::vector<uNode> list, const Position& pos)
        : Node(pos), m_list(move(list))
    {}

    std::vector<uNode>& ExeUnitNode::getList(){
        return m_list;
    }

    
    nlohmann::json ExeUnitNode::toJSON() const {
        nlohmann::json j{{"__class__", "ExeUnitNode"}};

        j["list"] = nlohmann::json::array();

        for (auto& n : m_list){
            j["list"].push_back(n->toJSON());
        }

        return j;
    }

    std::string ExeUnitNode::toString(){
        return "ExeUnitNode";
    }

    Object* ExeUnitNode::interpret(){
        assert(false);
        return nullptr;
    }

    void ExeUnitNode::accept(Visitor& visitor){
        visitor.visitExeUnitNode(*this);
    }
}