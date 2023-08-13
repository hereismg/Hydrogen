//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_POSITION_H
#define HDG_POSITION_H

#include <string>

namespace hdg {

    struct Indicator{
    public:
        int index;
        int line;
        int col;
    };

    class Position {
    protected:

        std::string* m_context;
        std::string m_fName;

        Indicator m_start;
        Indicator m_end;

        int m_iStart;
        int m_fStart[2];

        int m_iEnd;
        int m_fEnd[2];

    public:
        Position();
        Position(std::string* context, int iStart, int iEnd);
        Position(std::string* context, int iStart);
        Position(const Position& position);

        void setStart(int index, int line, int col);
        void setStart(const Indicator& index);
        Indicator getStart();

        void setEnd(int index, int line, int col);
        void setEnd(const Indicator& index);
        Indicator getEnd();


        void setIStart(int posStart);
        void setIEnd(int posEnd);
        [[nodiscard]] int getPosStart() const;
        [[nodiscard]] int getPosEnd() const;
        std::string* thisContext();

        std::string arrow();
    };

} // hdg

#endif //HDG_POSITION_H
