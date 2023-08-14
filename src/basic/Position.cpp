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

    void Position::setStart(int index, int line, int col){
        m_start.index = index;
        m_start.line = line;
        m_start.col = col;
    }

    void Position::setStart(const hdg::Indicator &indicator) {
        setStart(indicator.index, indicator.line, indicator.col);
    }

    void Position::setEnd(int index, int line, int col) {
        m_end.index = index;
        m_end.line = line;
        m_end.col = col;
    }

    void Position::setEnd(const hdg::Indicator &indicator) {
        setEnd(indicator.index, indicator.line, indicator.col);
    }

    std::string* Position::thisContext() {
        return m_context;
    }

    Indicator Position::getStart(){
        return m_start;
    }

    Indicator Position::getEnd() {
        return m_end;
    }

    std::string Position::getFilePath(){
        return m_fPath;
    };

    std::string Position::arrow() {
        return "^";
//        std::string arrowStart(m_start.col, ' ');
//        std::string arrowEnd(m_end.col - m_start.col, '^');
//        return m_context==nullptr ? "" : *m_context + "\n" + arrowStart + arrowEnd;
    }



} // hdg