#pragma once
#include "raylib.h"
#include "BSCS24009_piece.h"
#include <vector>
#include <string>

using namespace std;

class RaylibChess;

class BSCS24009_board {
private:
    vector<vector<BSCS24009_piece*>> grid;
    mColor currentTurn;
    RaylibChess* raylibUI;
    Pos selectedPos;
    Pos enPassantTarget;

public:
    BSCS24009_board(RaylibChess* ui = nullptr);
    ~BSCS24009_board();

    void showStartMenu();
    void initializeBoard();
    void clearBoard();
    bool movePiece(Pos from, Pos to);
    void display();
    void displayWithHighlight(Pos selectedPos);
    void LoadGame();
    void playGame();

    mColor getCurrentTurn() const;
    void switchTurn();
    BSCS24009_piece* getPiece(Pos pos) const;
    Pos getEnPassantTarget() const;
    void setEnPassantTarget(Pos pos);

    bool isValidSource(int row, int col, mColor playerColor) const;
    bool isValidDestination(int row, int col, mColor playerColor) const;

    void replacePiece(Pos pos, BSCS24009_piece* newPiece);
    void setPiece(Pos pos, BSCS24009_piece* piece);
    void removePiece(Pos pos);

    bool isInCheck(mColor color) const;
    bool isCheckmate(mColor color);
    bool isStalemate(mColor color);
    bool isSquareAttacked(Pos pos, mColor byColor) const;
    vector<Pos> getAllPossibleMoves(mColor color) const;
    Pos findKingPosition(mColor color) const;
    bool isValidMove(Pos from, Pos to, mColor playerColor);
    bool hasLegalMoves(mColor color);
    void highlight(int srcRow, int srcCol);
    void promotePawn(int row, int col);
};