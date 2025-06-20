#pragma once

#include <vector>

#include "Object.h"
#include "../node/unit_node.h"

namespace hdg {
    using std::vector;

    class BaseStateMachine: public Object{
    protected:
        std::unique_ptr<new_ExeUnitNode> unit;

    public:
        
    };
} // namespace hdg
