#pragma once
#include "raylib.h"
#include "BSCS24009_board.h"
#include <vector>
#include <string>
using namespace std;

class RaylibChess {
private:
    Texture2D boardTexture;
    vector<Texture2D> pieceTextures;
    const int boardSize = 800;
    const int squareSize = boardSize / 8;

    enum PieceTexture {
        PAWN_W, ROOK_W, KNIGHT_W, BISHOP_W, QUEEN_W, KING_W,
        PAWN_B, ROOK_B, KNIGHT_B, BISHOP_B, QUEEN_B, KING_B
    };

public:
    RaylibChess();
    ~RaylibChess();

    void LoadTextures();
    void UnloadTextures();
    void DrawBoard(BSCS24009_board* board);
    void DrawPieces(BSCS24009_board* board);
    void HighlightSquare(int row, int col, Color color);
    void GetBoardPositionFromMouse(int& row, int& col);
    void DrawPromotionMenu(mColor color);
    char GetPromotionChoice();
};