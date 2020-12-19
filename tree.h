#ifndef TREE_H
#define TREE_H

#include "graph.h"
#include "node.h"
#include <vector>
#include<unordered_set>


class Tree{
public:

    Tree(const Node& root);
    Tree(const Graph& graph, const Node& root);


    std::vector<Node> pathTo(const Node& node) const;
    std::unordered_set<Node> nodes() const;
    std::unordered_set<Edge> edges() const;


    void addChild(const Node& to, const Node& child, int weight);

private:

    Graph graph_;
    Node root_;


    std::unordered_set<Node> visitedNodes_;


    void visit(const Node& node);
    bool isVisited(const Node& node);
    bool hasUnvisitedChild(const Node& node);
    Node anUnvisitedChild(const Node& of);
    std::vector<Node> dfs(const Node& node, const Node& target, std::vector<Node> path);

};

#endif // TREE_H
