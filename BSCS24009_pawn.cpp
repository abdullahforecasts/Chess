#include "BSCS24009_pawn.h"
#include "BSCS24009_queen.h"
#include "BSCS24009_rook.h"
#include "BSCS24009_bishop.h"
#include "BSCS24009_knight.h"
#include "BSCS24009_board.h"
#include <iostream>

BSCS24009_pawn::BSCS24009_pawn(mColor c, Pos p, BSCS24009_board* b) : BSCS24009_piece(c, p, b) {}

char BSCS24009_pawn::draw() const {
    return color == PWHITE ? 'P' : 'p';
}

bool BSCS24009_pawn::isLegalMove(Pos newPos) const {
    int dr = newPos.ri - position.ri;
    int dc = abs(newPos.ci - position.ci);
    int dir = (color == PWHITE) ? -1 : 1;

    if (dc == 0 && dr == dir && !board->getPiece(newPos))
        return true;

    if (dc == 0 && dr == 2 * dir) {
        bool onStartingRank = (color == PWHITE && position.ri == 6) ||
            (color == PBLACK && position.ri == 1);
        if (!onStartingRank) return false;

        Pos intermediatePos = { position.ri + dir, position.ci };
        if (!board->getPiece(intermediatePos) && !board->getPiece(newPos))
            return true;
    }

    if (dc == 1 && dr == dir) {
        if (board->getPiece(newPos) && board->getPiece(newPos)->getColor() != color)
            return true;

        if (!board->getPiece(newPos)) {
            Pos epTarget = board->getEnPassantTarget();
            if (newPos.ri == epTarget.ri && newPos.ci == epTarget.ci) {
                Pos adjacentPos = { position.ri, newPos.ci };
                BSCS24009_piece* adjacentPiece = board->getPiece(adjacentPos);
                if (adjacentPiece && adjacentPiece->getColor() != color) {
                    if (dynamic_cast<BSCS24009_pawn*>(adjacentPiece)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void BSCS24009_pawn::promote() {
    if ((color == PWHITE && position.ri == 0) || (color == PBLACK && position.ri == 7)) {
        char choice;
        cout << "Promote pawn to (Q/R/B/N): ";
        cin >> choice;

        BSCS24009_piece* newPiece = nullptr;
        switch (toupper(choice)) {
        case 'Q': newPiece = new BSCS24009_queen(color, position, board); break;
        case 'R': newPiece = new BSCS24009_rook(color, position, board); break;
        case 'B': newPiece = new BSCS24009_bishop(color, position, board); break;
        case 'N': newPiece = new BSCS24009_knight(color, position, board); break;
        default: newPiece = new BSCS24009_queen(color, position, board);
        }
        board->replacePiece(position, newPiece);
    }
}