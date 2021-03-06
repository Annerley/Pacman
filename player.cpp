#include "player.h"
#include <QTimer>
#include <cassert>
#include <QKeyEvent>
#include <QDebug>
#include <QBrush>
#include<QPixmap>
#include <QGraphicsEllipseItem>
#include "game.h"

Player::Player(Game *game, int stepSize, QGraphicsItem *parent):
    movementDirection_(Direction::NONE),
    stepSize_(stepSize),
    QGraphicsEllipseItem(parent),
    game_(game)
{

     moveTimer = new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(300);


    setRect(0,0,stepSize,stepSize);
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

    setFlag(QGraphicsItem::ItemIsFocusable,true);
}

void Player::keyPressEvent(QKeyEvent *keyPress){
    switch (keyPress->key()){
    case Qt::Key_Up:
        movementDirection_ = Direction::UP;
        break;
    case Qt::Key_Down:
        movementDirection_ = Direction::DOWN;
        break;
    case Qt::Key_Left:
        movementDirection_ = Direction::LEFT;
        break;
    case Qt::Key_Right:
        movementDirection_ = Direction::RIGHT;
        break;
    default:
        ;
    }
}

void Player::move(){
    if (frontBlocked()){
            return;
        }

    switch (movementDirection_){
    case Direction::UP:
        moveUp();
        break;
    case Direction::DOWN:
        moveDown();
        break;
    case Direction::LEFT:
        moveLeft();
        break;
    case Direction::RIGHT:
        moveRight();
        break;
    case Direction::NONE:
        break;
    default:
        assert(false);
    }

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                               << mapToScene(0, 0)
                                                               << mapToScene(-0.01, -0.01));


    foreach (QGraphicsItem *item, foundItems) {
            if (item == this)
                continue;
            if(item == game_->enemies_[0]){
                emit signalCheckGameOver();
            }
            if(item == game_->enemies_[1]){
                emit signalCheckGameOver();
            }
            if(item == game_->enemies_[2]){
                emit signalCheckGameOver();
            }
        }
}

void Player::moveUp(){
    setPos(x(),y()-stepSize_);
}

void Player::moveDown(){
    setPos(x(),y()+stepSize_);
}

void Player::moveLeft(){
    setPos(x()-stepSize_,y());
}

void Player::moveRight(){
    setPos(x()+stepSize_,y());
}

bool Player::frontBlocked(){
    int x = 0;
    int y = 0;
    Node cellPos = game_->pointToNode(pos());
    switch (movementDirection_){
    case Direction::UP:
        x = cellPos.x();
        y = cellPos.y() - 1;
        break;
    case Direction::DOWN:
        x = cellPos.x();
        y = cellPos.y() + 1;
        break;
    case Direction::LEFT:
        x = cellPos.x() - 1;
        y = cellPos.y();
        break;
    case Direction::RIGHT:
        x = cellPos.x() + 1;
        y = cellPos.y();
        break;
    }

    return game_->filled(x,y);
}

void Player::pause(){
    if(moveTimer->isActive())
    {
        moveTimer->stop();
    }
}
