#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game* game = new Game(16,12,50);
    game->show();
    return a.exec();
}
