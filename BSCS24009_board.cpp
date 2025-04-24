#include "BSCS24009_board.h"
#include "BSCS24009_raylibchess.h"
#include "BSCS24009_pawn.h"
#include "BSCS24009_rook.h"
#include "BSCS24009_knight.h"
#include "BSCS24009_bishop.h"
#include "BSCS24009_queen.h"
#include "BSCS24009_king.h"
#include <fstream>
#include <iostream>

BSCS24009_board::BSCS24009_board(RaylibChess* ui) : currentTurn(PWHITE), raylibUI(ui), selectedPos({ -1, -1 }), enPassantTarget({ -1, -1 }) {
    grid.resize(8, vector<BSCS24009_piece*>(8, nullptr));
}

BSCS24009_board::~BSCS24009_board() {
    clearBoard();
}

void BSCS24009_board::initializeBoard() {
    clearBoard();
    for (int i = 0; i < 8; i++) {
        grid[1][i] = new BSCS24009_pawn(PBLACK, { 1,i }, this);
        grid[6][i] = new BSCS24009_pawn(PWHITE, { 6,i }, this);
    }

    grid[0][0] = new BSCS24009_rook(PBLACK, { 0,0 }, this);
    grid[0][7] = new BSCS24009_rook(PBLACK, { 0,7 }, this);
    grid[7][0] = new BSCS24009_rook(PWHITE, { 7,0 }, this);
    grid[7][7] = new BSCS24009_rook(PWHITE, { 7,7 }, this);

    grid[0][1] = new BSCS24009_knight(PBLACK, { 0,1 }, this);
    grid[0][6] = new BSCS24009_knight(PBLACK, { 0,6 }, this);
    grid[7][1] = new BSCS24009_knight(PWHITE, { 7,1 }, this);
    grid[7][6] = new BSCS24009_knight(PWHITE, { 7,6 }, this);

    grid[0][2] = new BSCS24009_bishop(PBLACK, { 0,2 }, this);
    grid[0][5] = new BSCS24009_bishop(PBLACK, { 0,5 }, this);
    grid[7][2] = new BSCS24009_bishop(PWHITE, { 7,2 }, this);
    grid[7][5] = new BSCS24009_bishop(PWHITE, { 7,5 }, this);

    grid[0][3] = new BSCS24009_queen(PBLACK, { 0,3 }, this);
    grid[7][3] = new BSCS24009_queen(PWHITE, { 7,3 }, this);

    grid[0][4] = new BSCS24009_king(PBLACK, { 0,4 }, this);
    grid[7][4] = new BSCS24009_king(PWHITE, { 7,4 }, this);
}

void BSCS24009_board::clearBoard() {
    for (auto& row : grid) {
        for (auto& piece : row) {
            delete piece;
            piece = nullptr;
        }
    }
}

Pos BSCS24009_board::getEnPassantTarget() const {
    return enPassantTarget;
}

void BSCS24009_board::setEnPassantTarget(Pos pos) {
    enPassantTarget = pos;
}

bool BSCS24009_board::movePiece(Pos from, Pos to) {
    BSCS24009_piece* piece = getPiece(from);
    if (!piece) return false;

    enPassantTarget = { -1, -1 };

    if (BSCS24009_king* king = dynamic_cast<BSCS24009_king*>(piece)) {
        if (!king->getHasMoved() && abs(to.ci - from.ci) == 2) {
            if (!king->isCastlingPossible(to)) return false;
            king->performCastling(to);
        }
        king->setMoved();
    }

    if (BSCS24009_rook* rook = dynamic_cast<BSCS24009_rook*>(piece)) {
        rook->setMoved();
    }

    if (BSCS24009_pawn* pawn = dynamic_cast<BSCS24009_pawn*>(piece)) {
        if (abs(to.ri - from.ri) == 2) {
            int epRow = (pawn->getColor() == PWHITE) ? to.ri + 1 : to.ri - 1;
            enPassantTarget = { epRow, to.ci };
        }
        else if (to.ci != from.ci && !getPiece(to)) {
            Pos capturedPos = { from.ri, to.ci };
            if (BSCS24009_piece* captured = getPiece(capturedPos)) {
                if (dynamic_cast<BSCS24009_pawn*>(captured)) {
                    delete captured;
                    grid[capturedPos.ri][capturedPos.ci] = nullptr;
                }
            }
        }
    }

    if (BSCS24009_piece* target = getPiece(to)) {
        delete target;
    }

    grid[to.ri][to.ci] = piece;
    grid[from.ri][from.ci] = nullptr;
    piece->setPosition(to);
    return true;
}

mColor BSCS24009_board::getCurrentTurn() const {
    return currentTurn;
}

void BSCS24009_board::switchTurn() {
    currentTurn = (currentTurn == PWHITE) ? PBLACK : PWHITE;
}

BSCS24009_piece* BSCS24009_board::getPiece(Pos pos) const {
    if (pos.ri >= 0 && pos.ri < 8 && pos.ci >= 0 && pos.ci < 8) {
        return grid[pos.ri][pos.ci];
    }
    return nullptr;
}

bool BSCS24009_board::isValidSource(int row, int col, mColor playerColor) const {
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;
    BSCS24009_piece* source = getPiece({ row,col });
    return source && source->getColor() == playerColor;
}

bool BSCS24009_board::isValidDestination(int row, int col, mColor playerColor) const {
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;
    BSCS24009_piece* dest = getPiece({ row,col });
    return !dest || dest->getColor() != playerColor;
}

//bool BSCS24009_board::movePiece(Pos from, Pos to) {
//    BSCS24009_piece* piece = getPiece(from);
//    if (!piece) return false;
//
//    if (BSCS24009_king* king = dynamic_cast<BSCS24009_king*>(piece)) {
//        if (!king->getHasMoved() && abs(to.ci - from.ci) == 2) {
//            if (!king->isCastlingPossible(to)) return false;
//            king->performCastling(to);
//        }
//        king->setMoved();
//    }
//
//    if (BSCS24009_rook* rook = dynamic_cast<BSCS24009_rook*>(piece)) {
//        rook->setMoved();
//    }
//
//    if (BSCS24009_pawn* pawn = dynamic_cast<BSCS24009_pawn*>(piece)) {
//        if (abs(to.ci - from.ci) == 1 && !getPiece(to)) {
//            Pos capturedPos = { from.ri, to.ci };
//            if (BSCS24009_piece* captured = getPiece(capturedPos)) {
//                if (BSCS24009_pawn* capturedPawn = dynamic_cast<BSCS24009_pawn*>(captured)) {
//                    delete capturedPawn;
//                    grid[capturedPos.ri][capturedPos.ci] = nullptr;
//                }
//            }
//        }
//    }
//
//    if (BSCS24009_piece* target = getPiece(to)) {
//        delete target;
//    }
//
//    grid[to.ri][to.ci] = piece;
//    grid[from.ri][from.ci] = nullptr;
//    piece->setPosition(to);
//    return true;
//}

//bool BSCS24009_board::movePiece(Pos from, Pos to) {
//    BSCS24009_piece* piece = getPiece(from);
//    if (!piece) return false;
//
//    if (BSCS24009_king* king = dynamic_cast<BSCS24009_king*>(piece)) {
//        if (!king->getHasMoved() && abs(to.ci - from.ci) == 2) {
//            if (!king->isCastlingPossible(to)) return false;
//            king->performCastling(to);
//        }
//        king->setMoved();
//    }
//
//    if (BSCS24009_rook* rook = dynamic_cast<BSCS24009_rook*>(piece)) {
//        rook->setMoved();
//    }
//
//    if (BSCS24009_piece* target = getPiece(to)) {
//        delete target;
//    }
//
//    grid[to.ri][to.ci] = piece;
//    grid[from.ri][from.ci] = nullptr;
//    piece->setPosition(to);
//    return true;
//}

void BSCS24009_board::display() {
    raylibUI->DrawBoard(this);
    raylibUI->DrawPieces(this);
}

void BSCS24009_board::showStartMenu() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("CHESS GAME", 250, 200, 50, BLACK);
        DrawText("1. New Game", 300, 300, 30, BLACK);
        DrawText("2. Load Game", 300, 350, 30, BLACK);

        if (IsKeyPressed(KEY_ONE)) {
            initializeBoard();
            break;
        }
        else if (IsKeyPressed(KEY_TWO)) {
            LoadGame();
            break;
        }

        EndDrawing();
    }
}

void BSCS24009_board::displayWithHighlight(Pos selectedPos) {
    raylibUI->DrawBoard(this);

    if (selectedPos.ri != -1 && selectedPos.ci != -1) {
        raylibUI->HighlightSquare(selectedPos.ri, selectedPos.ci, YELLOW);

        BSCS24009_piece* piece = getPiece(selectedPos);
        if (piece && piece->getColor() == currentTurn) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Pos testPos = { i, j };
                    BSCS24009_piece* target = getPiece(testPos);

                    
                    if (target && target->getColor() == currentTurn) {
                        continue;
                    }

                    if (piece->isLegalMove(testPos) && isValidMove(selectedPos, testPos, currentTurn)) {
                      
                        Color highlightColor = (target && target->getColor() != currentTurn) ? RED : GREEN;
                        raylibUI->HighlightSquare(i, j, highlightColor);
                    }
                }
            }
        }
    }

    raylibUI->DrawPieces(this);
}

void BSCS24009_board::playGame() {
   // initializeBoard();
    showStartMenu();
    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int row, col;
            raylibUI->GetBoardPositionFromMouse(row, col);

            if (row != -1 && col != -1) {
                if (selectedPos.ri == -1) {
                    if (isValidSource(row, col, currentTurn)) {
                        highlight(row, col);
                    }
                }
                else {
                    if (isValidDestination(row, col, currentTurn) &&
                        getPiece(selectedPos)->isLegalMove({ row, col }) &&
                        isValidMove(selectedPos, { row, col }, currentTurn)) {

                        movePiece(selectedPos, { row, col });

                        if (BSCS24009_pawn* pawn = dynamic_cast<BSCS24009_pawn*>(getPiece({ row, col }))) {
                            if ((currentTurn == PWHITE && row == 0) || (currentTurn == PBLACK && row == 7)) {
                                promotePawn(row, col);
                            }
                        }

                        switchTurn();
                    }
                    selectedPos = { -1, -1 };
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        displayWithHighlight(selectedPos);

       
        if (isCheckmate(currentTurn )) {
            const char* winner = (currentTurn == PWHITE) ? "BLACK" : "WHITE";
            DrawText(TextFormat("CHECKMATE! %s WINS!", winner), 100, 350, 40, RED);
          
        }
        else if (isStalemate(currentTurn)) {
            DrawText("STALEMATE! GAME DRAWN!", 150, 350, 40, ORANGE);
           
        }
         if (isInCheck(currentTurn))
          {
            DrawText("CHECK!", 10, 800 + 70, 20, RED);
         }

        EndDrawing();
    }
}

void BSCS24009_board::highlight(int srcRow, int srcCol) {
    if (!isValidSource(srcRow, srcCol, currentTurn)) return;
    selectedPos = { srcRow, srcCol };
}

void BSCS24009_board::promotePawn(int row, int col) {
    raylibUI->DrawPromotionMenu(currentTurn);

    char choice = 0;
    while (choice == 0 && !WindowShouldClose()) {
        choice = raylibUI->GetPromotionChoice();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        displayWithHighlight(selectedPos);
        raylibUI->DrawPromotionMenu(currentTurn);
        EndDrawing();
    }

    mColor color = getPiece({ row, col })->getColor();
    delete grid[row][col];
    grid[row][col] = nullptr;

    switch (choice) {
    case 'Q': grid[row][col] = new BSCS24009_queen(color, { row, col }, this); break;
    case 'R': grid[row][col] = new BSCS24009_rook(color, { row, col }, this); break;
    case 'B': grid[row][col] = new BSCS24009_bishop(color, { row, col }, this); break;
    case 'N': grid[row][col] = new BSCS24009_knight(color, { row, col }, this); break;
    }
}

bool BSCS24009_board::isSquareAttacked(Pos pos, mColor byColor) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            BSCS24009_piece* piece = grid[i][j];
            if (piece && piece->getColor() == byColor) {
                Pos attackerPos = { i,j };
                if (piece->isLegalMove(pos)) {
                    if (dynamic_cast<BSCS24009_pawn*>(piece)) {
                        int attackDir = (byColor == PWHITE) ? -1 : 1;
                        if (abs(pos.ci - j) == 1 && pos.ri - i == attackDir) {
                            return true;
                        }
                    }
                    else {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool BSCS24009_board::isInCheck(mColor color) const {
    Pos kingPos = findKingPosition(color);
   // cout << endl;
   //
   // cout << kingPos.ri << kingPos.ci << endl;
   //// exit(0);
    if (kingPos.ri == -1) return false;
    return isSquareAttacked(kingPos, color == PWHITE ? PBLACK : PWHITE);
}



bool BSCS24009_board::hasLegalMoves(mColor color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pos from = { i,j };
            BSCS24009_piece* piece = getPiece(from);
            if (piece && piece->getColor() == color) {
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        Pos to = { x,y };

                      
                        //cout << "Checking " << piece->draw() << " at "
                        //    << from.ri << "," << from.ci
                        //    << " to " << to.ri << "," << to.ci << endl;

                        if (from.ri == to.ri && from.ci == to.ci) continue;

                        Pos kingPos = findKingPosition(color);
                        if (to.ri == kingPos.ri && to.ci == kingPos.ci) continue;

                        if (piece->isLegalMove(to) && isValidMove(from, to, color)) {
                           /* cout << "VALID MOVE FOUND: " << piece->draw()
                                << " from " << from.ri << "," << from.ci
                                << " to " << to.ri << "," << to.ci << endl;*/
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

Pos BSCS24009_board::findKingPosition(mColor color) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            BSCS24009_piece* piece = grid[i][j];
            if (piece && piece->getColor() == color) {
                if (dynamic_cast<BSCS24009_king*>(piece)) {
                    return { i,j };
                }
            }
        }
    }
    return { -1,-1 };
}

vector<Pos> BSCS24009_board::getAllPossibleMoves(mColor color) const {
    vector<Pos> allMoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            BSCS24009_piece* piece = grid[i][j];
            if (piece && piece->getColor() == color) {
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        Pos move = { x,y };
                        if (piece->isLegalMove(move)) {
                            allMoves.push_back(move);
                        }
                    }
                }
            }
        }
    }
    return allMoves;
}

bool BSCS24009_board::isCheckmate(mColor color) {
  /*  int v = -1;
    v = (isInCheck(color) && !hasLegalMoves(color));
    cout << "\ncehck mate :    " << v << "\n\n\n\n";
    if (v==1)
    {
        exit(0);
    }*/
    
    return isInCheck(color) && !hasLegalMoves(color);
}

bool BSCS24009_board::isStalemate(mColor color) {
    return !isInCheck(color) && !hasLegalMoves(color);
}

bool BSCS24009_board::isValidMove(Pos from, Pos to, mColor playerColor) {
    BSCS24009_piece* piece = getPiece(from);
    if (!piece || !piece->isLegalMove(to)) return false;

    BSCS24009_piece* temp = grid[to.ri][to.ci];
    grid[to.ri][to.ci] = piece;
    grid[from.ri][from.ci] = nullptr;

    bool inCheckAfterMove = isInCheck(playerColor);

    grid[from.ri][from.ci] = piece;
    grid[to.ri][to.ci] = temp;

    return !inCheckAfterMove;
}

void BSCS24009_board::replacePiece(Pos pos, BSCS24009_piece* newPiece) {
    delete grid[pos.ri][pos.ci];
    grid[pos.ri][pos.ci] = newPiece;
}

void BSCS24009_board::setPiece(Pos pos, BSCS24009_piece* piece) {
    grid[pos.ri][pos.ci] = piece;
}

void BSCS24009_board::removePiece(Pos pos) {
    grid[pos.ri][pos.ci] = nullptr;
}

void BSCS24009_board::LoadGame() {
    ifstream rdr("grid.txt");
    char ch;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            rdr >> ch;
            if (ch == '.') grid[i][j] = nullptr;
            else if (ch == 'p') grid[i][j] = new BSCS24009_pawn(PBLACK, { i,j }, this);
            else if (ch == 'q') grid[i][j] = new BSCS24009_queen(PBLACK, { i,j }, this);
            else if (ch == 'r') grid[i][j] = new BSCS24009_rook(PBLACK, { i,j }, this);
            else if (ch == 'n') grid[i][j] = new BSCS24009_knight(PBLACK, { i,j }, this);
            else if (ch == 'b') grid[i][j] = new BSCS24009_bishop(PBLACK, { i,j }, this);
            else if (ch == 'k') grid[i][j] = new BSCS24009_king(PBLACK, { i,j }, this);
            else if (ch == 'P') grid[i][j] = new BSCS24009_pawn(PWHITE, { i,j }, this);
            else if (ch == 'Q') grid[i][j] = new BSCS24009_queen(PWHITE, { i,j }, this);
            else if (ch == 'R') grid[i][j] = new BSCS24009_rook(PWHITE, { i,j }, this);
            else if (ch == 'N') grid[i][j] = new BSCS24009_knight(PWHITE, { i,j }, this);
            else if (ch == 'B') grid[i][j] = new BSCS24009_bishop(PWHITE, { i,j }, this);
            else if (ch == 'K') grid[i][j] = new BSCS24009_king(PWHITE, { i,j }, this);
        }
    }
}