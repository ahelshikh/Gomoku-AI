#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>

// Define piece types
enum Piece {
    NONE = 0,
    BLACK = 1,
    WHITE = 2
};

// Define game type (currently only BOT is used)
enum GameType {
    NONEGAME = 0,
    BOT = 1
};

class GameModel {
public:
    int boardSize;
    std::vector<std::vector<int>> board;
    bool isWin;
    bool isDeadGame;
    int playerFlag; // current player's piece (BLACK or WHITE)
    GameType gameType;

    GameModel();
    void startGame(GameType type);
    void actionByPerson(int row, int col);
    bool checkWin(int row, int col);
    bool checkDeadGame();
};

#endif // GAMEMODEL_H

