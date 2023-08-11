//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_FUNCTION_H
#define HDG_FUNCTION_H

#include <vector>
#include "../basic/Environment.h"]
#include "../node/Node.h"
#include "../node/ObjAssignNode.h"
#include "Object.h"

namespace hdg {

    class Function: public Object{
    protected:
        std::vector<ObjAssignNode*> m_args;

        Environment* m_environment;
        Node* m_body;

    public:
        ~Function() override;

        Object* parenthesis(std::initializer_list<Object*> list);

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_FUNCTION_H
