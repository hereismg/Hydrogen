//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/basic/Position.h"

namespace hdg {

    Position::Position():
        m_context(nullptr), m_posStart(0), m_posEnd(0){
    }

    Position::Position(std::string* context, int posStart, int posEnd):
        m_context(context), m_posStart(posStart), m_posEnd(posEnd){
    }

    Position::Position(std::string *context, int posStart):
        m_context(context), m_posStart(posStart), m_posEnd(posStart+1){
    }

    Position::Position(const Position &position) = default;

    void Position::setPosStart(int posStart) {
        m_posStart = posStart;
    }

    void Position::setPosEnd(int posEnd) {
        m_posEnd = posEnd;
    }

    int Position::getPosStart() const {
        return m_posStart;
    }

    int Position::getPosEnd() const {
        return m_posEnd;
    }

    std::string* Position::thisContext() {
        return m_context;
    }

    std::string Position::arrow() {
        std::string arrowStart(m_posStart, ' ');
        std::string arrowEnd(m_posEnd-m_posStart, '^');
        return m_context==nullptr ? "" : *m_context + "\n" + arrowStart + arrowEnd;
    }



} // hdg