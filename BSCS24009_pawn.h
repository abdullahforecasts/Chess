#pragma once
#include "BSCS24009_piece.h"

class BSCS24009_pawn : public BSCS24009_piece {
public:
    BSCS24009_pawn(mColor c, Pos p, BSCS24009_board* b);
    char draw() const override;
    bool isLegalMove(Pos newPos) const override;
    void promote();
};