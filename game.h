#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "player.h"
#include <vector>


class Game: public QGraphicsView {
    Q_OBJECT
public:
    // constructors
    Game( int numCellsWide,  int numCellsLong,
          int cellSize, QWidget* parent=nullptr);

    // modifiers ("setters")

    void fill( int x,  int y);
    bool filled(int x, int y);

    // helper functions (readers)

public slots:

private:
    // main private attributes

    QGraphicsScene* scene_;       // scene
    Player* player_;              // player

    int cellSize_;       // cell size

    // helper functions


};

#endif // GAME_H
