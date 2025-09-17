#include <QApplication>
#include "mainwindow.h"

/**
 * @brief Entry point of the application.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
