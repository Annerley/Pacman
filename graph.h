#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>
#include "node.h"
#include "edge.h"

class Tree;

class Graph{
public:

    Graph();
    Graph(const std::unordered_set<Node>& nodes, const std::unordered_set<Edge>& edges);


    std::unordered_set<Node> nodes() const;
    std::unordered_set<Edge> edges() const;
    std::vector<Edge> outgoingEdges(const Node& from) const;
    std::vector<Edge> incomingEdges(const Node& to) const;
    std::vector<Node> outgoingNodes(const Node& from) const;
    std::vector<Node> incomingNodes(const Node& to) const;
    bool contains(const Node& node) const;
    bool contains(const Edge& edge) const;
    std::vector<Node> shortestPath(const Node& from, const Node& to) const;
    Tree spt(const Node& source) const;


    void addNode(const Node& node);
    void addEdge(const Node& from, const Node& to,  int weight);

private:

    std::unordered_set<Node> nodes_;
    std::unordered_set<Edge> edges_;


    std::unordered_set<Node> pickedNodes_;
    std::unordered_set<Node> unpickedNodes_;
    std::unordered_set<Edge> pickedEdges_;
    std::unordered_set<Edge> unpickedEdges_;
    std::unordered_map<Node, int> nodeWeight_;
    std::unordered_map<Node,Edge> updatedEdge_;


    void pick(const Node& node);
    void pick(const Edge& edge);
    bool picked(const Node& node) const;
    bool picked(const Edge& edge) const;
    void setWeight(const Node& of,  int weight);
    int weight(const Node& of) const;
    Edge edge(const Node& from, const Node& to) const;
    void unpickAll();
    void initializeNodeWeights(const Node& source);
    bool hasUnpickedNode() const;
    Node lightestUnpickedNode() const;
    void pickConnetedEdge(const Node& of);
    std::vector<Node> unpickedNeighbors(const Node& of) const;
    void updateNeighborWeights(const Node& of);

};

#endif // GRAPH_H
