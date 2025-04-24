#pragma once
#include "BSCS24009_piece.h"

class BSCS24009_king : public BSCS24009_piece {
private:
    bool hasMoved;
public:
    BSCS24009_king(mColor c, Pos p, BSCS24009_board* b);
    char draw() const override;
    bool isLegalMove(Pos newPos) const override;
    void setMoved();
    bool getHasMoved() const;
    bool isCastlingPossible(Pos newPos) const;
    void performCastling(Pos newPos);
};