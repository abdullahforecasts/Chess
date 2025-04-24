#include "BSCS24009_knight.h"
#include <iostream>
BSCS24009_knight::BSCS24009_knight(mColor c, Pos p, BSCS24009_board* b) : BSCS24009_piece(c, p, b) {}

char BSCS24009_knight::draw() const {
    return color == PWHITE ? 'N' : 'n';
}

bool BSCS24009_knight::isLegalMove(Pos newPos) const {
    int dr = abs(newPos.ri - position.ri);
    int dc = abs(newPos.ci - position.ci);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}