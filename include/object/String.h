//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_STRING_H
#define HDG_STRING_H

#include "Object.h"

namespace hdg {

    class String: public Object {
    protected:
        std::string m_value;

    public:
        String();
        String(std::string value);
        String(std::string value, const Position& position);
        ~String() override;

        std::string getValue();

        Object* plus(Object* other) override;
        bool isTrue() override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_STRING_H
