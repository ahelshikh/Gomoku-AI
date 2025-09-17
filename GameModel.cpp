#include "GameModel.h"

GameModel::GameModel() {
    boardSize = 15;
    board.assign(boardSize, std::vector<int>(boardSize, NONE));
    isWin = false;
    isDeadGame = false;
    playerFlag = BLACK; // Black moves first.
    gameType = NONEGAME;
}

void GameModel::startGame(GameType type) {
    board.assign(boardSize, std::vector<int>(boardSize, NONE));
    isWin = false;
    isDeadGame = false;
    playerFlag = BLACK;
    gameType = type;
}

void GameModel::actionByPerson(int row, int col) {
    if (row < 0 || row >= boardSize || col < 0 || col >= boardSize)
        return;
    if (board[row][col] != NONE)
        return;
    board[row][col] = playerFlag;
    if (checkWin(row, col)) {
        isWin = true;
        return;
    }
    if (checkDeadGame()) {
        isDeadGame = true;
        return;
    }
    // Switch turn.
    playerFlag = (playerFlag == BLACK) ? WHITE : BLACK;
}

bool GameModel::checkWin(int row, int col) {
    int current = board[row][col];
    if (current == NONE)
        return false;

    // Check four directions: horizontal, vertical, main diagonal, anti-diagonal.
    int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
    for (int i = 0; i < 4; ++i) {
        int count = 1;
        int dx = directions[i][0], dy = directions[i][1];
        // Count in the positive direction.
        int tx = row + dx, ty = col + dy;
        while (tx >= 0 && tx < boardSize && ty >= 0 && ty < boardSize && board[tx][ty] == current) {
            count++;
            tx += dx;
            ty += dy;
        }
        // Count in the negative direction.
        tx = row - dx;
        ty = col - dy;
        while (tx >= 0 && tx < boardSize && ty >= 0 && ty < boardSize && board[tx][ty] == current) {
            count++;
            tx -= dx;
            ty -= dy;
        }
        if (count >= 5)
            return true;
    }
    return false;
}

bool GameModel::checkDeadGame() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == NONE)
                return false;
        }
    }
    return true;
}