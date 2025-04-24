#include "BSCS24009_rook.h"

BSCS24009_rook::BSCS24009_rook(mColor c, Pos p, BSCS24009_board* b) : BSCS24009_piece(c, p, b), hasMoved(false) {}

char BSCS24009_rook::draw() const {
    return color == PWHITE ? 'R' : 'r';
}

bool BSCS24009_rook::isLegalMove(Pos newPos) const {
    return isVerticalPathClear(position, newPos) || isHorizontalPathClear(position, newPos);
}

void BSCS24009_rook::setMoved() { hasMoved = true; }
bool BSCS24009_rook::getHasMoved() const { return hasMoved; }