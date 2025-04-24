#pragma once
#include "BSCS24009_rook.h"
#include "BSCS24009_bishop.h"

class BSCS24009_queen : public BSCS24009_rook, public BSCS24009_bishop {
public:
    BSCS24009_queen(mColor c, Pos p, BSCS24009_board* b);
    char draw() const override;
    bool isLegalMove(Pos newPos) const override;
};