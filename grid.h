#ifndef PATHGRID_H
#define PATHGRID_H

#include <vector>
#include "node.h"
#include <unordered_map>
#include "graph.h"

class PathGrid{
public:

    PathGrid( int numCols,  int numRows);


    std::vector<Node> nodes() const;
    bool filled(const Node& node) const;
    bool filled( int x,  int y) const;
    std::vector<Node> unfilledNeighbors(const Node& of) const;
    Graph graph() const;
    std::vector<Node> shortestPath(const Node& from, const Node& to) const;
    std::vector<Node> column( int i) const;
    std::vector<Node> row( int i) const;


    void fill(const Node& node);
    void fill( int x,  int y);
    void unfill(const Node& node);
    void unfill( int x,  int y);
    void fillColumn( int i);
    void fillRow( int i);
    void setFilling(const std::vector<std::vector<int>>& vec);

private:

    std::vector<std::vector<Node>> nodes_;
    std::unordered_map<Node,bool> filled_;

};

#endif // PATHGRID_H
