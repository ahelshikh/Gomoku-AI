#include "MainWindow.h"
#include "GameAI.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Initialize the game model.
    game = new GameModel;
    game->gameType = BOT;
    game->startGame(game->gameType);

    // Create a central widget and a grid layout.
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    gridLayout = new QGridLayout(centralWidget);
    centralWidget->setLayout(gridLayout);

    // Set up the board (create buttons).
    setupBoard();

    setWindowTitle("Gomoku - Player vs AI");
    resize(700, 700);
}

MainWindow::~MainWindow() {
    delete game;
}

void MainWindow::setupBoard() {
    int boardSize = game->boardSize;
    buttons.resize(boardSize);
    for (int i = 0; i < boardSize; ++i) {
        buttons[i].resize(boardSize);
        for (int j = 0; j < boardSize; ++j) {
            QPushButton *button = new QPushButton("", this);
            button->setFixedSize(40, 40);
            gridLayout->addWidget(button, i, j);
            buttons[i][j] = button;
            // Connect button clicks using a lambda capturing row and column.
            connect(button, &QPushButton::clicked, [=]() {
                // Do nothing if the game has ended or the cell is already occupied.
                if (game->isWin || game->isDeadGame || game->board[i][j] != NONE)
                    return;
                // Process player's move.
                game->actionByPerson(i, j);
                updateBoard();
                if (game->isWin) {
                    QMessageBox::information(this, "Game Over", "Player wins!");
                    return;
                }
                // Let the AI make its move.
                if (game->gameType == BOT && !game->isWin) {
                    GameAI::actionByAI(*game, 3); // Adjust search depth as desired.
                    updateBoard();
                    if (game->isWin) {
                        QMessageBox::information(this, "Game Over", "AI wins!");
                    }
                }
            });
        }
    }
}

void MainWindow::updateBoard() {
    int boardSize = game->boardSize;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (game->board[i][j] == BLACK)
                buttons[i][j]->setText("B");
            else if (game->board[i][j] == WHITE)
                buttons[i][j]->setText("W");
            else
                buttons[i][j]->setText("");
        }
    }
}


