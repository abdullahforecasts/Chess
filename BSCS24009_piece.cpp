#include "BSCS24009_piece.h"
#include "BSCS24009_board.h"

BSCS24009_piece::BSCS24009_piece(mColor c, Pos p, BSCS24009_board* b)
    : color(c), position(p), board(b) {
}

bool BSCS24009_piece::isVerticalPathClear(Pos source, Pos destination) const {
    if (!isVerticalMove(source, destination)) return false;

    int step = (destination.ri > source.ri) ? 1 : -1;
    int i = source.ri + step;

    while (i != destination.ri) {
        if (i < 0 || i >= 8) break;
        if (board->getPiece({ i, source.ci })) {
            return false;
        }
        i += step;
    }
    return true;
}

bool BSCS24009_piece::isHorizontalPathClear(Pos source, Pos destination) const {
    if (!isHorizontalMove(source, destination)) return false;

    int step = (destination.ci > source.ci) ? 1 : -1;
    int i = source.ci + step;

    while (i != destination.ci) {
        if (i < 0 || i >= 8) break;
        if (board->getPiece({ source.ri, i })) {
            return false;
        }
        i += step;
    }
    return true;
}

//bool BSCS24009_piece::isVerticalPathClear(Pos source, Pos destination) const {
//    if (source.ci != destination.ci) return false;
//
//    int step = (destination.ri > source.ri) ? 1 : -1;
//    for (int i = source.ri + step; i != destination.ri; i += step) {
//        if (board->getPiece({ i, source.ci })) {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool BSCS24009_piece::isHorizontalPathClear(Pos source, Pos destination) const {
//    if (source.ri != destination.ri) return false;
//
//    int step = (destination.ci > source.ci) ? 1 : -1;
//    for (int i = source.ci + step; i != destination.ci; i += step) {
//        if (board->getPiece({ source.ri, i })) {
//            return false;
//        }
//    }
//    return true;
//}

bool BSCS24009_piece::isDiagonalPathClear(Pos source, Pos destination) const {
    int rowDir = (destination.ri > source.ri) ? 1 : -1;
    int colDir = (destination.ci > source.ci) ? 1 : -1;

    int row = source.ri + rowDir;
    int col = source.ci + colDir;

    while (row >= 0 && row < 8 && col >= 0 && col < 8) {
        if (row == destination.ri && col == destination.ci) {
            break;
        }
        if (board->getPiece({ row, col })) {
            return false;
        }
        row += rowDir;
        col += colDir;
    }
    return true;
}

bool BSCS24009_piece::isPathClear(Pos from, Pos to) const {
    if (isVerticalMove(from, to)) {
        return isVerticalPathClear(from, to);
    }
    else if (isHorizontalMove(from, to)) {
        return isHorizontalPathClear(from, to);
    }
    else {
        return isDiagonalPathClear(from, to);
    }
}

bool BSCS24009_piece::isVerticalMove(Pos source, Pos destination) const {
    return (destination.ci == source.ci);
}

bool BSCS24009_piece::isHorizontalMove(Pos source, Pos destination) const {
    return (destination.ri == source.ri);
}