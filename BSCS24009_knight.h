#pragma once
#include "BSCS24009_piece.h"

class BSCS24009_knight : public BSCS24009_piece {
public:
    BSCS24009_knight(mColor c, Pos p, BSCS24009_board* b);
    char draw() const override;
    bool isLegalMove(Pos newPos) const override;
};