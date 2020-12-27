#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "player.h"
#include "map.h"
#include "enemy.h"
#include <vector>

#define GAME_STOPED 0
#define GAME_STARTED 1

class Game: public QGraphicsView {
    Q_OBJECT
public:

    Game( int numCellsWide,  int numCellsLong,
          int cellSize, QWidget* parent=nullptr);

    void createEnemy( int x,  int y);

    void fill( int x,  int y);
    bool filled(int x, int y);

    Node pointToNode(const QPointF& point);
    QPointF nodeToPoint(const Node& node);
    std::vector<Enemy*> enemies_;

public slots:
    void setEnemyPathsToPlayer();
     void slotGameOver();                        // Слот инициализации Game Over
private:

     PathingMap pathingMap_;
    QGraphicsScene* scene_;
    Player* player_;
     int             gameState;
    int cellSize_;


    void drawMap(const std::vector<std::vector<int>>& vec);

};

#endif // GAME_H
