//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_POSITION_H
#define HDG_POSITION_H

#include <string>

namespace hdg {

    class Position {
    protected:
        std::string* m_context;
        int m_posStart;
        int m_posEnd;

    public:
        Position();
        Position(std::string* context, int posStart, int posEnd);
        Position(std::string* context, int posStart);
        Position(const Position& position);

        void setPosStart(int posStart);
        void setPosEnd(int posEnd);
        [[nodiscard]] int getPosStart() const;
        [[nodiscard]] int getPosEnd() const;
        std::string* thisContext();

        std::string arrow();
    };

} // hdg

#endif //HDG_POSITION_H
