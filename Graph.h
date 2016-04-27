/*-------------------------------------------------
// CSCI 2270 Data Structures                     //
// Spring 2016                                   //
// Final Project                                 //
// Alex Thompson                                 //
-------------------------------------------------*/

/*-----------------------------------------------------------------
Header file for my modified graph class.
-----------------------------------------------------------------*/

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    int ID;
    vertex *parent;
    std::string name;
    bool visited;
    bool solved;
    int distance;
    std::vector<adjVertex> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string newName);
        std::vector<vertex*> shortestPath(std::string startingCity, std::string endingCity);
        void BFTraversal(std::string startingCity);                                             // traverses graph using Breadth-first search
        void DFTraversal(std::string startingCity);                                             // traverses graph using Depth-first search
        void printVertices();
        void resetVertexStatus();                                                               // resets all nodes in the graph so that subsequent searches/traversals
                                                                                                // are possible
        vertex* findVertex(std::string name);

    private:
        std::vector<vertex*> vertices;
        std::vector<vertex*> dijkstraSP(std::string startingCity, std::string endingCity);      // four algorithms the user can choose between when deciding how they
        std::vector<vertex*> bellmanFordSP(std::string startingCity, std::string endingCity);   // want to move from one node to another: a basic breadth-first search,
        std::vector<vertex*> breadthFirstSP(std::string startingCity, std::string endingCity);  // basic depth-first search, Dijkstra's Algorithm, and an algorithm
        std::vector<vertex*> depthFirstSP(std::string startingCity, std::string endingCity);    // called the Bellman-Ford algorithm.
};

#endif // GRAPH_H
