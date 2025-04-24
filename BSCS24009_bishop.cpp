#include "BSCS24009_bishop.h"
#include<iostream>
BSCS24009_bishop::BSCS24009_bishop(mColor c, Pos p, BSCS24009_board* b)
    : BSCS24009_piece(c, p, b) {
}

char BSCS24009_bishop::draw() const {
    return color == PWHITE ? 'B' : 'b';
}

bool BSCS24009_bishop::isLegalMove(Pos newPos) const {
    // return true;
    int dr = abs(newPos.ri - position.ri);
    int dc = abs(newPos.ci - position.ci);
    // return dr == dc;
    return dr == dc && isDiagonalPathClear(position, newPos);
}