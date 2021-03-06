#include "tree.h"
#include <cassert>

Tree::Tree(const Node &root): root_(root), graph_(){

    graph_.addNode(root);
}

Tree::Tree(const Graph &graph, const Node &root): graph_(graph), root_(root){

}

void Tree::addChild(const Node &to, const Node &child, int weight){
    assert(graph_.contains(to));

    graph_.addNode(child);

    graph_.addEdge(to,child,weight);
}

std::vector<Node> Tree::pathTo(const Node &node) const{
    Tree copy  = *this;
    std::vector<Node> empty;
    return copy.dfs(root_,node,empty);
}

std::unordered_set<Node> Tree::nodes() const{
    return graph_.nodes();
}

std::unordered_set<Edge> Tree::edges() const{
    return graph_.edges();
}

std::vector<Node> Tree::dfs(const Node &node, const Node &target, std::vector<Node> path){

    visit(node);

    if (node == target){
        path.push_back(node);
        return path;
    }


    if (!hasUnvisitedChild(node)){
        Node lastNode = path.back();
        path.pop_back();
        return dfs(lastNode,target,path);
    }

    if (hasUnvisitedChild(node)){
        path.push_back(node);
        Node unvisited = anUnvisitedChild(node);
        return dfs(unvisited,target,path);
    }

}

void Tree::visit(const Node &node){
    //assert(graph_.contains(node));

    visitedNodes_.insert(node);
}

bool Tree::isVisited(const Node &node){
    return (visitedNodes_.count(node) == 1);
}

bool Tree::hasUnvisitedChild(const Node &node){

    std::vector<Node> children = graph_.outgoingNodes(node);


    int numUnvisited = 0;
    for (auto child : children){
        if (!isVisited(child)){
            numUnvisited++;
        }
    }

    return (numUnvisited > 0);
}

Node Tree::anUnvisitedChild(const Node &of){

    assert(hasUnvisitedChild(of));


    std::vector<Node> children = graph_.outgoingNodes(of);


    for (auto child : children){
        if (!isVisited(child)){
            return child;
        }
    }

}
