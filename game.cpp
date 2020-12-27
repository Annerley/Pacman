#include "game.h"
#include <cassert>
#include <QDebug>
#include <QTimer>
#include<QGraphicsScene>
#include<QGraphicsRectItem>
#include <QMessageBox>

Game::Game( int numCellsWide,  int numCellsLong,  int cellSize, QWidget *parent):
    QGraphicsView(parent),
    pathingMap_(numCellsWide,numCellsLong,cellSize),
    scene_(new QGraphicsScene(this)),
    player_(new Player(this,cellSize)),
    enemies_(),
    cellSize_(cellSize)
{

    setScene(scene_);
    setSceneRect(0,0,numCellsWide*cellSize,numCellsLong*cellSize);

    player_->setPos(3*cellSize,1*cellSize);
    scene_->addItem(player_);
    player_->setFocus();

    createEnemy(1,1);
    createEnemy(1,2);
    createEnemy(1,10);


    std::vector<std::vector<int>> vec {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,0,0,1,1,0,0,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,0,0,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
     drawMap(vec);

     QTimer* followTimer = new QTimer(this);
        connect(followTimer,SIGNAL(timeout()),this,SLOT(setEnemyPathsToPlayer()));
        followTimer->start(1000);

      connect(player_, &Player::signalCheckGameOver, this, &Game::slotGameOver);


}

void Game::createEnemy( int x,  int y){
    Enemy* enemy = new Enemy(cellSize_);
    enemy->setPos(cellSize_*x,cellSize_*y);
    scene_->addItem(enemy);
    enemies_.push_back(enemy);
}

void Game::fill( int x,  int y){
    pathingMap_.fillCell(x,y);

    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,cellSize_,cellSize_);
    rect->setPos(x*cellSize_,y*cellSize_);
    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    rect->setBrush(brush);
    scene_->addItem(rect);
}

bool Game::filled(int x, int y){
    return pathingMap_.filledCell(x,y);
}

void Game::setEnemyPathsToPlayer(){
    for (Enemy* enemy:enemies_){
        std::vector<Node> nodePath = pathingMap_.shortestPath(enemy->pos().x(),
                                                              enemy->pos().y(),
                                                              player_->pos().x(),
                                                              player_->pos().y());
        std::vector<QPointF> path;
        for (Node node:nodePath){
            path.push_back(QPointF(node.x(),node.y()));
        }

        enemy->setPoints(path);
    }
}


void Game::drawMap(const std::vector<std::vector<int> > &vec){

    assert(vec.size() == pathingMap_.numCellsLong());
    assert(vec[0].size() == pathingMap_.numCellsWide());


    for (int y = 0, n = pathingMap_.numCellsLong(); y < n; y++){
        for (int x = 0, p = pathingMap_.numCellsWide(); x < p; x++){
            if (vec[y][x] != 0){
                fill(x,y);
            }
        }
    }
}

Node Game::pointToNode(const QPointF &point){
    return Node(point.x()/cellSize_,point.y()/cellSize_);
}


QPointF Game::nodeToPoint(const Node &node){
    return QPointF(node.x()*cellSize_,node.y()*cellSize_);
}

void Game::slotGameOver()
{
    /* Если игра окончена
     * Отключаем все таймеры
     * */

    QMessageBox::warning(this,
                         "Game Over",
                         "I express my regrets, but you lost");


}
