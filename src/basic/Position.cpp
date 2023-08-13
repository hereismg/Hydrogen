//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/basic/Position.h"

namespace hdg {

    Position::Position():
            m_context(nullptr), m_iStart(0), m_iEnd(0){
    }

    Position::Position(std::string* context, int start, int end):
            m_context(context), m_iStart(start), m_iEnd(end){
    }

    Position::Position(std::string *context, int iStart):
            m_context(context), m_iStart(iStart), m_iEnd(iStart + 1){
    }

    Position::Position(const Position &position) = default;

    void Position::setIStart(int posStart) {
        m_iStart = posStart;
    }

    void Position::setIEnd(int posEnd) {
        m_iEnd = posEnd;
    }

    int Position::getPosStart() const {
        return m_iStart;
    }

    int Position::getPosEnd() const {
        return m_iEnd;
    }

    std::string* Position::thisContext() {
        return m_context;
    }

    std::string Position::arrow() {
        std::string arrowStart(m_iStart, ' ');
        std::string arrowEnd(m_iEnd - m_iStart, '^');
        return m_context==nullptr ? "" : *m_context + "\n" + arrowStart + arrowEnd;
    }



} // hdg