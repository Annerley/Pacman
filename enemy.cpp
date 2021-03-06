#include "enemy.h"
#include <QLineF>
#include <QTimer>

#include <QBrush>
#include <cassert>


Enemy::Enemy( int stepSize, QGraphicsItem *parent):
    QGraphicsRectItem(parent),
    targetPoint_(0),
    stepSize_(stepSize),
    points_()
{

     moveTimer = new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(500);


    setRect(0,0,stepSize,stepSize);
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

}


void Enemy::move(){

    if (atLastPoint()){
        return;
    }


    moveTowardsTarget();


    if (targetReached()){
        setNextTarget();
    }



}


void Enemy::setPoints(const std::vector<QPointF> &points){

    points_ = points;

    targetPoint_ = 1;
}


bool Enemy::targetReached(){
    const int EPSILON = 50;


    QPointF target = points_[targetPoint_];
    QLineF line(pos(),target);

    return (line.length() < EPSILON);
}

bool Enemy::atLastPoint(){

    int veclength = points_.size();
    int targetPt = targetPoint_;
    bool cond = targetPt >= veclength;
    return (cond);
}


void Enemy::setNextTarget(){

    ++targetPoint_;
}

void Enemy::moveTowardsTarget(){

    QPointF target = points_[targetPoint_];
    QLineF line(pos(),target);
    line.setLength(stepSize_);
    moveBy(line.dx(),line.dy());
}

void Enemy::pause(){

    if(moveTimer->isActive())
    {
        moveTimer->stop();
    }



}
