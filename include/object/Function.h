//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_FUNCTION_H
#define HDG_FUNCTION_H

#include <sstream>
#include "../basic/Environment.h"
#include "../node/Node.h"
#include "../node/ObjAssignNode.h"
#include "../object/None.h"
#include "Object.h"

namespace hdg {

    class Function: public Object{
    protected:
        std::string m_name;
        std::vector<ObjAssignNode*> m_args;
        Environment* m_environment;

        Node* m_body;
    public:
        Function();
        Function(std::string name, std::vector<ObjAssignNode*>args, Environment* environment, Node* body, const Position& position);
        ~Function() override;

        Object* parenthesis(const std::vector<Object*>& list) override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_FUNCTION_H
