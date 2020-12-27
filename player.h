#ifndef PLAYER_H
#define PLAYER_H


#include <QGraphicsRectItem>
#include <QObject>


class QKeyEvent;
class QGraphicsItem;
class Game;

class Player: public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:

    Player(Game* game, int stepSize, QGraphicsItem* parent = nullptr);


    enum class Direction {UP, DOWN, LEFT, RIGHT, NONE};


    void keyPressEvent(QKeyEvent* keyPress);

public slots:
    void move();
signals:
    void signalCheckGameOver();  // Сигнал на вызов состояния Game Over

private:

    Direction movementDirection_;
    int stepSize_;
    Game* game_;


    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool frontBlocked();

};

#endif // PLAYER_H
