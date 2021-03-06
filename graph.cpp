#include "graph.h"
#include <vector>
#include <cassert>
#include "tree.h"
#include <QDebug> // TODO remove


Graph::Graph(){

}


Graph::Graph(const std::unordered_set<Node> &nodes, const std::unordered_set<Edge> &edges): nodes_(nodes),edges_(edges){

}


void Graph::addNode(const Node &node){
    nodes_.insert(node);
}


void Graph::addEdge(const Node &from, const Node &to,  int weight){

    assert(contains(from));
    assert(contains(to));

    Edge edge(from,to,weight);

    edges_.insert(edge);
}


std::unordered_set<Node> Graph::nodes() const{
    return nodes_;
}


std::unordered_set<Edge> Graph::edges() const{
    return edges_;
}


std::vector<Edge> Graph::outgoingEdges(const Node &from) const{
    //assert(contains(from));

    std::vector<Edge> edges;
    for(auto edge : edges_){
        if (edge.from() == from){
            edges.push_back(edge);
        }
    }
    return edges;
}


std::vector<Edge> Graph::incomingEdges(const Node &to) const{
    assert(contains(to));

    std::vector<Edge> edges;
    for(auto edge : edges_){
        if (edge.to() == to){
            edges.push_back(edge);
        }
    }
    return edges;
}


std::vector<Node> Graph::outgoingNodes(const Node &from) const{

    //assert(contains(from));


    std::vector<Edge> outgoingE = outgoingEdges(from);


    std::vector<Node> outgoingN;
    for (auto edge:outgoingE){
        outgoingN.push_back(edge.to());
    }

    return outgoingN;
}


std::vector<Node> Graph::incomingNodes(const Node &to) const{

    assert(contains(to));

    std::vector<Edge> incomingE = incomingEdges(to);

    std::vector<Node> incomingN;
    for (auto edge:incomingE){
        incomingN.push_back(edge.from());
    }

    return incomingN;
}


bool Graph::contains(const Node &node) const{
    return (nodes_.count(node) == 1);
}


bool Graph::contains(const Edge &edge) const{
    return (edges_.count(edge) == 1);
}


std::vector<Node> Graph::shortestPath(const Node &from, const Node &to) const{
    Tree t = spt(from);
    std::vector<Node> path = t.pathTo(to);
    return path;
}


Tree Graph::spt(const Node &source) const{

    assert(contains(source));


    Graph copy = *this;


    Node rootNode(0,0);


    copy.unpickAll();


    copy.initializeNodeWeights(source);


    bool isFirstNode = true;
    while (copy.hasUnpickedNode()){

        Node lightest = copy.lightestUnpickedNode();
        copy.pick(lightest);


        copy.updateNeighborWeights(lightest);


        if (isFirstNode){
            rootNode = lightest;
            isFirstNode = false;
            continue;
        }


        copy.pickConnetedEdge(lightest);
    }


    Graph graph(copy.pickedNodes_,copy.pickedEdges_);


    return Tree(graph,rootNode);

}

void Graph::pick(const Node &node){

    assert(unpickedNodes_.count(node) == 1);


    assert(!picked(node));

    pickedNodes_.insert(node);
    unpickedNodes_.erase(node);

}

void Graph::pick(const Edge &edge){

    pickedEdges_.insert(edge);
    unpickedEdges_.erase(edge);
}

bool Graph::picked(const Node &node) const{

    assert(contains(node));

    return (pickedNodes_.count(node) == 1);
}

bool Graph::picked(const Edge &edge) const{

    assert(contains(edge));

    return (pickedEdges_.count(edge) == 1);
}

void Graph::setWeight(const Node &of,  int weight){
    assert(contains(of));

    nodeWeight_[of] = weight;
}


 int Graph::weight(const Node &of) const{

    assert(contains(of));

    int weight = nodeWeight_.find(of)->second;
    return weight;
}

Edge Graph::edge(const Node &from, const Node &to) const{

    assert(contains(from));
    assert(contains(to));

    for (Edge edge:edges_){
        if (edge.from() == from && edge.to() == to){
            return edge;
        }
    }


    assert(true);
    return Edge();
}


void Graph::unpickAll(){

    for (Node node:nodes_){
        unpickedNodes_.insert(node);
    }


    for (Edge edge:edges_){
        unpickedEdges_.insert(edge);
    }
}


void Graph::initializeNodeWeights(const Node &source){

    assert(contains(source));


    setWeight(source,0);


    for (Node node:nodes_){
        if (!(node == source)){
            setWeight(node,1000);
        }
    }
}


bool Graph::hasUnpickedNode() const{
    return (!unpickedNodes_.empty());
}


Node Graph::lightestUnpickedNode() const{

    assert(hasUnpickedNode());

    Node lightest = *(unpickedNodes_.begin());

    for (Node node: unpickedNodes_){
        if (weight(node) < weight(lightest)){
            lightest = node;
        }
    }

    return lightest;
}


void Graph::pickConnetedEdge(const Node &of){
    Edge edge = updatedEdge_[of];
    pick(edge);

}


std::vector<Node> Graph::unpickedNeighbors(const Node &of) const{
    std::vector<Node> neighbors = outgoingNodes(of);

    std::vector<Node> unpicked;
    for (auto neighbor:neighbors){
        if (!picked(neighbor)){
            unpicked.push_back(neighbor);
        }
    }

    return unpicked;

}


void Graph::updateNeighborWeights(const Node &of){

    for (Node neighbor:unpickedNeighbors(of)){

        Edge edgeToNeighbor = edge(of,neighbor);
        int edgeWeight = edgeToNeighbor.weight();


        int newTotalWeight = nodeWeight_[of] + edgeWeight;
        int oldWeight = nodeWeight_[neighbor];

        if (newTotalWeight < oldWeight){
            setWeight(neighbor,newTotalWeight);

            updatedEdge_[neighbor] = edgeToNeighbor;
        }

    }
}
