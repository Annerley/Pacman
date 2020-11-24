#include "game.h"
#include <cassert>
#include <QDebug>
#include <QTimer>
#include<QGraphicsScene>
#include<QGraphicsRectItem>

Game::Game( int numCellsWide,  int numCellsLong,  int cellSize, QWidget *parent):
    QGraphicsView(parent),
    pathingMap_(numCellsWide,numCellsLong,cellSize),
    scene_(new QGraphicsScene(this)),
    player_(new Player(this,cellSize)),
    cellSize_(cellSize)
{
    //set size of window/scene
    setScene(scene_);
    setSceneRect(0,0,numCellsWide*cellSize,numCellsLong*cellSize);

    // add the player to the scene/give him keyboard focus
    player_->setPos(3*cellSize,1*cellSize);
    scene_->addItem(player_);
    player_->setFocus();



    // draw the map
    std::vector<std::vector<int>> vec {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
     drawMap(vec);




}

/// Fills the specified cell.
///
/// Marks it filled in the pathingMap_ and draws a gray square to visually
/// represent it.
void Game::fill( int x,  int y){
    pathingMap_.fillCell(x,y);

    // draw rectangle
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

void Game::drawMap(const std::vector<std::vector<int> > &vec){
    // make sure the vec is big enough to fill all the cell
    assert(vec.size() == pathingMap_.numCellsLong());
    assert(vec[0].size() == pathingMap_.numCellsWide());

    // draw map based on 2d vector
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

/// Returns a point representing the top left corner of the specified cell.
QPointF Game::nodeToPoint(const Node &node){
    return QPointF(node.x()*cellSize_,node.y()*cellSize_);
}

