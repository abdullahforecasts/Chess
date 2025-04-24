#pragma once
#include "BSCS24009_piece.h"
using namespace std;
class BSCS24009_bishop :virtual public BSCS24009_piece {
public:
    BSCS24009_bishop(mColor c, Pos p, BSCS24009_board* b);
    char draw() const override;
    bool isLegalMove(Pos newPos) const override;
};