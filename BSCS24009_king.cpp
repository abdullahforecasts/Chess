#include "BSCS24009_king.h"
#include "BSCS24009_board.h"
#include "BSCS24009_rook.h"

BSCS24009_king::BSCS24009_king(mColor c, Pos p, BSCS24009_board* b) : BSCS24009_piece(c, p, b), hasMoved(false) {}

char BSCS24009_king::draw() const {
    return color == PWHITE ? 'K' : 'k';
}

//bool BSCS24009_king::isLegalMove(Pos newPos) const {
//    int dr = abs(newPos.ri - position.ri);
//    int dc = abs(newPos.ci - position.ci);
//
//    if (dr <= 1 && dc <= 1) return true;
//    if (!hasMoved && dr == 0 && dc == 2) return isCastlingPossible(newPos);
//    return false;
//}
bool BSCS24009_king::isLegalMove(Pos newPos) const {
    // Check if moving to own piece's position
    if (board->getPiece(newPos) && board->getPiece(newPos)->getColor() == color) {
        return false;
    }

    int dr = abs(newPos.ri - position.ri);
    int dc = abs(newPos.ci - position.ci);

    // Normal king move (1 square in any direction)
    if (dr <= 1 && dc <= 1) return true;

    // Castling move
    if (!hasMoved && dr == 0 && dc == 2) {
        return isCastlingPossible(newPos);
    }

    return false;
}

bool BSCS24009_king::isCastlingPossible(Pos newPos) const {
    int direction = (newPos.ci > position.ci) ? 1 : -1;
    int rookCol = (direction == 1) ? 7 : 0;
    Pos rookPos = { position.ri, rookCol };

    if (!isHorizontalPathClear(position, rookPos)) return false;
    BSCS24009_piece* rook = board->getPiece(rookPos);
    if (!rook || rook->draw() != (color == PWHITE ? 'R' : 'r')) return false;

    BSCS24009_rook* castleRook = dynamic_cast<BSCS24009_rook*>(rook);
    return castleRook && !castleRook->getHasMoved();
}

void BSCS24009_king::performCastling(Pos newPos) {
    int direction = (newPos.ci > position.ci) ? 1 : -1;
    int rookCol = (direction == 1) ? 7 : 0;
    int newRookCol = (direction == 1) ? 5 : 3;

    Pos rookPos = { position.ri, rookCol };
    Pos newRookPos = { position.ri, newRookCol };

    BSCS24009_piece* rook = board->getPiece(rookPos);
    board->setPiece(newRookPos, rook);
    board->removePiece(rookPos);
    rook->setPosition(newRookPos);
}

void BSCS24009_king::setMoved() { hasMoved = true; }
bool BSCS24009_king::getHasMoved() const { return hasMoved; }