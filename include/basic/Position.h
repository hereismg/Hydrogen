//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_POSITION_H
#define HDG_POSITION_H

#include <string>

namespace hdg {

    struct Indicator{
    public:
        unsigned long long index;
        unsigned long long line;
        unsigned long long col;
    };

    class Position {
    protected:
        std::string m_fPath;
        std::string* m_context;

        Indicator m_start{};
        Indicator m_end{};

    public:
        Position();
        Position(std::string fPath, std::string* context, const Indicator& start, const Indicator& end);
        Position(std::string fPath, std::string* context, const Indicator& start);
        Position(const Position& position);

        void setStart(int index, int line, int col);
        void setStart(const Indicator& indicator);
        void setEnd(int index, int line, int col);
        void setEnd(const Indicator& indicator);

        Indicator getStart();
        Indicator getEnd();
        std::string getFilePath();
        std::string* thisContext();

        std::string arrow();
    };

} // hdg

#endif //HDG_POSITION_H
