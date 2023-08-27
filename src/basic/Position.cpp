//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/basic/Position.h"

namespace hdg {

    Position::Position(): m_context(nullptr){}

    Position::Position(std::string fPath, std::string* context, const Indicator& start, const Indicator& end):
            m_fPath(std::move(fPath)), m_context(context), m_start(start), m_end(end){}

    Position::Position(std::string fPath, std::string* context, const Indicator& start):
            m_fPath(std::move(fPath)), m_context(context), m_start(start), m_end(start.index+1, start.line, start.col+1){}

    Position::Position(const Position &position) {
        m_fPath = position.m_fPath;
        m_context = position.m_context;
        m_start = position.m_start;
        m_end = position.m_end;
    }

    void Position::setStart(unsigned long long index, unsigned long long line, unsigned long long col){
        m_start.index = index;
        m_start.line = line;
        m_start.col = col;
    }

    void Position::setStart(const Position::Indicator &indicator) {
        setStart(indicator.index, indicator.line, indicator.col);
    }

    void Position::setEnd(unsigned long long index, unsigned long long line, unsigned long long col) {
        m_end.index = index;
        m_end.line = line;
        m_end.col = col;
    }

    void Position::setEnd(const Position::Indicator &indicator) {
        setEnd(indicator.index, indicator.line, indicator.col);
    }

    std::string* Position::thisContext() {
        return m_context;
    }

    Position::Indicator Position::getStart(){
        return m_start;
    }

    Position::Indicator Position::getEnd() {
        return m_end;
    }

    std::string Position::getFilePath(){
        return m_fPath;
    };

    std::string Position::toString() {

        if (m_start.line == m_end.line){
            std::string result = "    " + std::to_string(m_start.line) + " | ";
            unsigned long long temp = result.size();

            unsigned long long left = 0, right = 0;
            left = m_start.index - m_start.col;
            for (right=m_end.index; right<m_context->size() && (*m_context)[right]!='\n'; right++);
            result += m_context->substr(left, right - left) + "\n";             /// @attention 这里的换行符一定要手动添加，而不是直接从原文中截取！！！

            std::string blanks(m_start.col+temp, ' ');
            std::string arrows(m_end.col - m_start.col, '^');
            result += blanks + arrows;

            return result;
        }
        else{
            return "m_start.line != m_end.line!!!";
        }
//        std::string arrowStart(m_start.col, ' ');
//        std::string arrowEnd(m_end.col - m_start.col, '^');
//        return m_context==nullptr ? "" : *m_context + "\n" + arrowStart + arrowEnd;
    }



} // hdg