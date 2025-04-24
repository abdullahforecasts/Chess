#pragma once
#include "BSCS24009_head.h"

class BSCS24009_board;

class BSCS24009_piece {
protected:
    mColor color;
    Pos position;
    BSCS24009_board* board;

    bool isVerticalMove(Pos source, Pos destination) const;
    bool isHorizontalMove(Pos source, Pos destination) const;
    bool isVerticalPathClear(Pos source, Pos destination) const;
    bool isHorizontalPathClear(Pos source, Pos destination) const;
    bool isDiagonalPathClear(Pos source, Pos destination) const;

public:
    BSCS24009_piece(mColor c, Pos p, BSCS24009_board* b);
    virtual ~BSCS24009_piece() = default;

    virtual char draw() const = 0;
    virtual bool isLegalMove(Pos newPos) const = 0;
    virtual bool isPathClear(Pos from, Pos to) const;
    mColor getColor() const { return color; }
    Pos getPosition() const { return position; }
    void setPosition(Pos p) { position = p; }
};