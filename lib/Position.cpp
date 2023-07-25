//
// Created by Magnesium on 2023/7/25.
//

#include "Position.h"

namespace hdg {
    Position::Position(const std::string &context, int posStart, int posEnd):
        context(context), posStart(posStart), posEnd(posEnd){
    }

    Position::Position(const Position &position):
        context(position.context), posStart(position.posStart), posEnd(position.posEnd){
    }

    void Position::setPosStart(int posStart) {
        this->posStart = posStart;
    }

    void Position::setPosEnd(int posEnd) {
        this->posEnd = posEnd;
    }

    int Position::getPosStart() {
        return posStart;
    }

    int Position::getPosEnd() {
        return posEnd;
    }

    const std::string &Position::getContext() {
        return context;
    }



} // hdg