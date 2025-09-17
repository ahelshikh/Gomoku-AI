#include "GameAI.h"
#include <limits>
#include <algorithm>

void GameAI::actionByAI(GameModel &game, int searchDepth) {
    if (game.isWin || game.isDeadGame)
        return;

    auto move = findBestMove(game, searchDepth);
    int bestRow = move.first, bestCol = move.second;
    if (bestRow < 0 || bestCol < 0)
        return;

    game.board[bestRow][bestCol] = game.playerFlag;
    if (game.checkWin(bestRow, bestCol)) {
        game.isWin = true;
        return;
    }
    if (game.checkDeadGame()) {
        game.isDeadGame = true;
        return;
    }
    // Switch turn.
    game.playerFlag = (game.playerFlag == BLACK) ? WHITE : BLACK;
}

std::pair<int, int> GameAI::findBestMove(GameModel &game, int depth) {
    int bestScore = std::numeric_limits<int>::min();
    int bestRow = -1, bestCol = -1;
    int currentPlayer = game.playerFlag;
    for (int r = 0; r < game.boardSize; ++r) {
        for (int c = 0; c < game.boardSize; ++c) {
            if (game.board[r][c] == NONE) {
                game.board[r][c] = currentPlayer;
                if (game.checkWin(r, c)) {
                    game.board[r][c] = NONE;
                    return {r, c};
                }
                game.playerFlag = (currentPlayer == BLACK) ? WHITE : BLACK;
                int score = alphaBeta(game, depth - 1, std::numeric_limits<int>::min(),
                                      std::numeric_limits<int>::max(), false);
                game.board[r][c] = NONE;
                game.playerFlag = currentPlayer;
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = r;
                    bestCol = c;
                }
            }
        }
    }
    return {bestRow, bestCol};
}

int GameAI::alphaBeta(GameModel &game, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth <= 0 || game.isWin || game.isDeadGame)
        return evaluateBoard(game);

    int currentPlayer = game.playerFlag;
    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int r = 0; r < game.boardSize; ++r) {
            for (int c = 0; c < game.boardSize; ++c) {
                if (game.board[r][c] == NONE) {
                    game.board[r][c] = currentPlayer;
                    if (game.checkWin(r, c)) {
                        game.board[r][c] = NONE;
                        return 999999; // Very high score for winning move.
                    }
                    game.playerFlag = (currentPlayer == BLACK) ? WHITE : BLACK;
                    int eval = alphaBeta(game, depth - 1, alpha, beta, false);
                    game.board[r][c] = NONE;
                    game.playerFlag = currentPlayer;
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            if (beta <= alpha)
                break;
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int r = 0; r < game.boardSize; ++r) {
            for (int c = 0; c < game.boardSize; ++c) {
                if (game.board[r][c] == NONE) {
                    game.board[r][c] = currentPlayer;
                    if (game.checkWin(r, c)) {
                        game.board[r][c] = NONE;
                        return -999999; // Very low score for opponent winning move.
                    }
                    game.playerFlag = (currentPlayer == BLACK) ? WHITE : BLACK;
                    int eval = alphaBeta(game, depth - 1, alpha, beta, true);
                    game.board[r][c] = NONE;
                    game.playerFlag = currentPlayer;
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

int GameAI::evaluateBoard(const GameModel &game) {
    int AI_PLAYER = game.playerFlag;
    int blackCount = 0;
    int whiteCount = 0;
    for (int r = 0; r < game.boardSize; ++r) {
        for (int c = 0; c < game.boardSize; ++c) {
            if (game.board[r][c] == BLACK)
                blackCount++;
            else if (game.board[r][c] == WHITE)
                whiteCount++;
        }
    }
    return (AI_PLAYER == BLACK) ? (blackCount - whiteCount) : (whiteCount - blackCount);
}

