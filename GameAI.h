#ifndef GAMEAI_H
#define GAMEAI_H

#include "GameModel.h"
#include <utility>

class GameAI {
public:
    // Executes the AI move using minimax with alpha-beta pruning.
    static void actionByAI(GameModel &game, int searchDepth);
    // Finds the best move for the AI.
    static std::pair<int, int> findBestMove(GameModel &game, int depth);

private:
    static int alphaBeta(GameModel &game, int depth, int alpha, int beta, bool maximizingPlayer);
    static int evaluateBoard(const GameModel &game);
};

#endif // GAMEAI_H
