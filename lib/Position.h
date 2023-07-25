//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_POSITION_H
#define HDG_POSITION_H

#include <string>

namespace hdg {

    class Position {
    private:
        const std::string& context;
        int posStart;
        int posEnd;

    public:
        Position(const std::string& context, int posStart, int posEnd);
        Position(const Position& position);

        void setPosStart(int posStart);
        void setPosEnd(int posEnd);
        int getPosStart();
        int getPosEnd();
        const std::string& getContext();
    };

} // hdg

#endif //HDG_POSITION_H
