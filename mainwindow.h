#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>
#include "GameModel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupBoard();
    void updateBoard();

    GameModel *game;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVector<QVector<QPushButton*>> buttons;
};

#endif // MAINWINDOW_H
