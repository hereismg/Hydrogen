//
// Created by Magnesium on 2023/8/9.
//

#ifndef HDG_OBJECTNODE_H
#define HDG_OBJECTNODE_H

#include "../Node.h"

namespace hdg {

    class ObjectNode: public Node{
    protected:
        std::string m_class;

    public:
        ObjectNode();
        ObjectNode(std::string className, const Position& position, Environment* environment);
        ObjectNode(const Position& position, Environment* environment);
        ~ObjectNode() override;

        void setClass(const std::string& className);
        std::string getClass();

        std::string toString() override = 0;
        virtual Object* interpret() = 0;
    };

} // hdg

#endif //HDG_OBJECTNODE_H
