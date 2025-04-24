#include "BSCS24009_queen.h"

BSCS24009_queen::BSCS24009_queen(mColor c, Pos p, BSCS24009_board* b) :
    BSCS24009_piece(c, p, b), BSCS24009_rook(c, p, b), BSCS24009_bishop(c, p, b) {
}

char BSCS24009_queen::draw() const {
    return color == PWHITE ? 'Q' : 'q';
}

bool BSCS24009_queen::isLegalMove(Pos newPos) const {
    return BSCS24009_rook::isLegalMove(newPos) || BSCS24009_bishop::isLegalMove(newPos);
}