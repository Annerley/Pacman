#include "game.h"
#include <cassert>
#include <QDebug>
#include <QTimer>
#include<QGraphicsScene>
#include<QGraphicsRectItem>

Game::Game( int numCellsWide,  int numCellsLong,  int cellSize, QWidget *parent):
    QGraphicsView(parent),
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




}

/// Fills the specified cell.
///
/// Marks it filled in the pathingMap_ and draws a gray square to visually
/// represent it.
void Game::fill( int x,  int y){


    // draw rectangle
    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,cellSize_,cellSize_);
    rect->setPos(x*cellSize_,y*cellSize_);
    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    rect->setBrush(brush);
    scene_->addItem(rect);
}


