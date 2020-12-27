#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <vector>
#include <QPointF>

class Enemy:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:

    Enemy( int stepSize, QGraphicsItem* parent=nullptr);
    QTimer* moveTimer;

    void setPoints(const std::vector<QPointF>& points);
    void pause();
public slots:

    void move();

private:

    std::vector<QPointF> points_;
    size_t targetPoint_;
    int stepSize_;


    bool targetReached();
    bool atLastPoint();
    void setNextTarget();
    void moveTowardsTarget();
};

#endif // ENEMY_H
