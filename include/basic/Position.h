//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_POSITION_H
#define HDG_POSITION_H

#include <string>

namespace hdg {

    /**
     * 
     * */
    class Position {
    public:

        /**
         * 文本坐标指示器。
         * @details     总的来说，文本坐标指示器主要存储某个位置的两类坐标。\n\n
         *              一类是该位置的内存索引号 index 。该索引号会算上包括换行符的全部字符。
         *              另一类是易于人类观看的二维坐标（line，col）。其中 line 从 1 开始索引， col从 0 开始索引。
         *
         * @warning     该结构体内部的三个变量都是无符号长整型（unsigned long long），所以要格外注意类型转换造成的问题。
         * */
        struct Indicator{
            unsigned long long index;
            unsigned long long line;
            unsigned long long col;
        };

    protected:
        std::string m_fPath;
        std::string* m_context;

        Indicator m_start{0, 0, 0};
        Indicator m_end{0, 0, 0};

    public:
        Position();
        Position(std::string fPath, std::string* context, const Indicator& start, const Indicator& end);
        Position(std::string fPath, std::string* context, const Indicator& start);
        Position(const Position& position);

        void setStart(unsigned long long index, unsigned long long line, unsigned long long col);
        void setStart(const Indicator& indicator);
        void setEnd(unsigned long long index, unsigned long long line, unsigned long long col);
        void setEnd(const Indicator& indicator);

        Indicator getStart();
        Indicator getEnd();
        std::string getFilePath();
        std::string* thisContext();

        std::string toString();
    };

} // hdg

#endif //HDG_POSITION_H
