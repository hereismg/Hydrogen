//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_FUNCTION_H
#define HDG_FUNCTION_H

#include <sstream>
#include "../../basic/Environment.h"
#include "../../node/Node.h"
#include "../../node/ObjAssignNode.h"
#include "../None.h"
#include "../Object.h"
#include "BaseFunction.h"

namespace hdg {

    class Function: public BaseFunction{
    protected:
        std::string m_name;
        Environment* m_environment{nullptr};

        Node* m_body{nullptr};
    public:
        Function();
        Function(std::string name, std::vector<ObjAssignNode*>args, Environment* environment, Node* body, const Position& position);
        ~Function() override;

        Object* parenthesis(const std::vector<Object*>& args) override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_FUNCTION_H
