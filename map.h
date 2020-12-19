#ifndef PATHINGMAP_H
#define PATHINGMAP_H

#include "grid.h"
#include <vector>

using namespace std;

class PathingMap{
public:

    PathingMap( int numCellsWide,  int numCellsLong,  int cellSize);


    bool filled( int x,  int y) const;
    bool filledCell( int x,  int y) const;
    std::vector<Node> nodes() const;
    std::vector<Node> shortestPath( int xfrom,  int yfrom,  int xto,  int yto) const;
    int width() const;
    int height() const;
    int cellSize() const;
    int numCellsLong() const;
    int numCellsWide() const;


    void fill( int x,  int y);
    void fillCell( int x,  int y);
    void fillColumn( int i);
    void fillRow( int i);
    void unfill( int x,  int y);
    void unfillCell( int x,  int y);
    void setFilling(const std::vector<std::vector<int>>& vec);

private:

    PathGrid pathGrid_;
    int cellSize_;
    int numCellsWide_;
    int numCellsLong_;
};

#endif // PATHINGMAP_H
