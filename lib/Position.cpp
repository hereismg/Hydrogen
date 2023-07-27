//
// Created by Magnesium on 2023/7/25.
//

#include "Position.h"

namespace hdg {
    Position::Position(const std::string &context, int posStart, int posEnd):
        m_context(context), m_posStart(posStart), m_posEnd(posEnd){
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

    const std::string &Position::getContext() {
        return m_context;
    }



} // hdg