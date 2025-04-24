#include "BSCS24009_raylibchess.h"
#include "BSCS24009_board.h"

RaylibChess::RaylibChess() {
    InitWindow(boardSize, boardSize + 100, "Chess Game");
    SetTargetFPS(60);
    LoadTextures();
}

RaylibChess::~RaylibChess() {
    UnloadTextures();
    CloseWindow();
}

void RaylibChess::LoadTextures() {
    Image boardImg = GenImageChecked(boardSize, boardSize, squareSize, squareSize, BEIGE,DARKPURPLE);
    boardTexture = LoadTextureFromImage(boardImg);
    UnloadImage(boardImg);

    vector<string> pieceFiles = {
        "pawnW.png", "rookW.png", "knightW.png", "bishopW.png", "queenW.png", "kingW.png",
        "pawnB.png", "rookB.png", "knightB.png", "bishopB.png", "queenB.png", "kingB.png"
    };

    for (const auto& file : pieceFiles) {
        pieceTextures.push_back(LoadTexture(file.c_str()));
    }
}

void RaylibChess::UnloadTextures() {
    UnloadTexture(boardTexture);
    for (auto& texture : pieceTextures) {
        UnloadTexture(texture);
    }
}

void RaylibChess::DrawBoard(BSCS24009_board* board) {
    DrawTexture(boardTexture, 0, 0, WHITE);

    Color turnColor = board->getCurrentTurn() == PWHITE ? WHITE : BLACK;
    DrawRectangle(0, boardSize, boardSize, 100, turnColor);

    const char* turnText = (board->getCurrentTurn() == PWHITE) ? "WHITE'S TURN" : "BLACK'S TURN";
    int textWidth = MeasureText(turnText, 30);
    DrawText(turnText, (boardSize - textWidth) / 2, boardSize + 35, 30,
        (turnColor.r == 255) ? BLACK : WHITE);

    if (board->isInCheck(board->getCurrentTurn())) {
        DrawText("CHECK!", 10, boardSize + 70, 20, RED);
    }
}

void RaylibChess::DrawPieces(BSCS24009_board* board) {
    float scale = (float)squareSize / 512.0f;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            BSCS24009_piece* piece = board->getPiece({ row, col });
            if (piece) {
                int textureIndex = -1;
                char pieceChar = piece->draw();

                switch (tolower(pieceChar)) {
                case 'p': textureIndex = (piece->getColor() == PWHITE) ? PAWN_W : PAWN_B; break;
                case 'r': textureIndex = (piece->getColor() == PWHITE) ? ROOK_W : ROOK_B; break;
                case 'n': textureIndex = (piece->getColor() == PWHITE) ? KNIGHT_W : KNIGHT_B; break;
                case 'b': textureIndex = (piece->getColor() == PWHITE) ? BISHOP_W : BISHOP_B; break;
                case 'q': textureIndex = (piece->getColor() == PWHITE) ? QUEEN_W : QUEEN_B; break;
                case 'k': textureIndex = (piece->getColor() == PWHITE) ? KING_W : KING_B; break;
                }

                if (textureIndex != -1) {
                    Vector2 position = {
                        col * squareSize + (squareSize - (512.0f * scale)) / 2,
                        row * squareSize + (squareSize - (512.0f * scale)) / 2
                    };
                    DrawTextureEx(pieceTextures[textureIndex], position, 0.0f, scale, WHITE);
                }
            }
        }
    }
}

void RaylibChess::HighlightSquare(int row, int col, Color color) {
    DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize,
        ColorAlpha(color, 0.5f));
}

void RaylibChess::GetBoardPositionFromMouse(int& row, int& col) {
    Vector2 mousePos = GetMousePosition();
    if (mousePos.y < boardSize) {
        row = (int)(mousePos.y / squareSize);
        col = (int)(mousePos.x / squareSize);
    }
    else {
        row = col = -1;
    }
}

void RaylibChess::DrawPromotionMenu(mColor color) {
    Color bgColor = color == PWHITE ? WHITE : BLACK;
    Color textColor = color == PWHITE ? BLACK : WHITE;

    DrawRectangle(0, boardSize / 2 - 50, boardSize, 100, bgColor);
    DrawText("PROMOTE PAWN TO:", boardSize / 2 - 150, boardSize / 2 - 30, 20, textColor);

    const char* options = "Q - Queen  R - Rook  B - Bishop  N - Knight";
    DrawText(options, boardSize / 2 - 200, boardSize / 2 + 10, 30, textColor);
}

char RaylibChess::GetPromotionChoice() {
    int key = GetCharPressed();
    if (key >= 'a' && key <= 'z') key = toupper(key);

    if (key == 'Q' || key == 'R' || key == 'B' || key == 'N') {
        return (char)key;
    }
    return 0;
}