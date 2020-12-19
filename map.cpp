#include "map.h"


PathingMap::PathingMap( int numCellsWide,  int numCellsLong,  int cellSize):
    numCellsWide_(numCellsWide),
    numCellsLong_(numCellsLong),
    cellSize_(cellSize),
    pathGrid_(numCellsWide,numCellsLong) {


}


bool PathingMap::filled( int x,  int y) const{

    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    return pathGrid_.filled(xGrid,yGrid);
}


bool PathingMap::filledCell( int x,  int y) const{
    return pathGrid_.filled(x,y);
}


std::vector<Node> PathingMap::nodes() const{

    std::vector<Node> nodes;


    for (Node node:pathGrid_.nodes()){

        int scaledX = (node.x() * cellSize_);
        int scaledY = (node.y() * cellSize_);
        node.setX(scaledX);
        node.setY(scaledY);
        nodes.push_back(node);
    }

    return nodes;
}

std::vector<Node> PathingMap::shortestPath( int xfrom,  int yfrom,  int xto,  int yto) const{

    std::vector<Node> path = pathGrid_.shortestPath(Node(xfrom/cellSize_,yfrom/cellSize_),Node(xto/cellSize_,yto/cellSize_));
    std::vector<Node> scaledPath;


    for (Node node:path){

        int scaledX = (node.x() * cellSize_);
        int scaledY = (node.y() * cellSize_);
        node.setX(scaledX);
        node.setY(scaledY);
        scaledPath.push_back(node);
    }

    return scaledPath;
}


int PathingMap::width() const{
    return cellSize_ * numCellsWide_;
}


int PathingMap::height() const{
    return cellSize_ * numCellsLong_;
}


int PathingMap::cellSize() const{
    return cellSize_;
}


int PathingMap::numCellsLong() const{
    return numCellsLong_;
}

int PathingMap::numCellsWide() const{
    return numCellsWide_;
}

void PathingMap::fill( int x,  int y){
    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    pathGrid_.fill(xGrid,yGrid);
}

void PathingMap::fillCell( int x,  int y){
    pathGrid_.fill(x,y);
}

void PathingMap::fillColumn( int i){
    pathGrid_.fillColumn(i);
}

void PathingMap::fillRow( int i){
    pathGrid_.fillRow(i);
}

void PathingMap::unfill( int x,  int y){
    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    pathGrid_.unfill(xGrid,yGrid);
}

void PathingMap::unfillCell( int x,  int y){
    pathGrid_.unfill(x,y);
}

void PathingMap::setFilling(const std::vector<std::vector<int> > &vec){
    pathGrid_.setFilling(vec);
}
