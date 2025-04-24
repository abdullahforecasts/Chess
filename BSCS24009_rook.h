#pragma once
#include "BSCS24009_piece.h"

class BSCS24009_rook : virtual public BSCS24009_piece {
private:
    bool hasMoved;
public:
    BSCS24009_rook(mColor c, Pos p, BSCS24009_board* b);
    char draw() const override;
    bool isLegalMove(Pos newPos) const override;
    void setMoved();
    bool getHasMoved() const;
};