#include "BSCS24009_board.h"
#include "BSCS24009_raylibchess.h"

int main() {
   
    RaylibChess ui;
    BSCS24009_board board(&ui);
    board.playGame();

    return 0;
}