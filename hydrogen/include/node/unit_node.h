#pragma once

#include "Node.h"

namespace hdg{
    class ExeUnitNode;
    typedef std::unique_ptr<ExeUnitNode> uExeUnitNode;

    class ExeUnitNode:public Node{
    protected:
        std::vector<uNode> m_list;

    public:
        ExeUnitNode() = default;
        ExeUnitNode(std::vector<uNode> list);
        ExeUnitNode(std::vector<uNode> list, const Position& pos);
        
        ~ExeUnitNode() = default;

        ExeUnitNode(const ExeUnitNode&) = delete;
        ExeUnitNode& operator=(const ExeUnitNode&) = delete;
        
        ExeUnitNode(ExeUnitNode&&) noexcept = default;
        ExeUnitNode& operator=(ExeUnitNode&&) noexcept = default;

        std::vector<uNode>& getList();

        virtual nlohmann::json toJSON() const override;
        virtual std::string toString() override;
        virtual Object* interpret() override;
        virtual void accept(Visitor& visitor) override;
    };
}
