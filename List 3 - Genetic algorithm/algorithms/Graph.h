#ifndef LISTA3_GRAPH_H
#define LISTA3_GRAPH_H

#include <vector>
#include <iostream>

using namespace std;


class Graph {
private:
    vector<vector<double>> adjacencyMatrix;
public:
    Graph(){};
    // Constructor for creating a graph with a given number of vertices
    Graph(int numVertices) {
        adjacencyMatrix.resize(numVertices, vector<double>(numVertices));
    }

    // Method for adding an edge to the graph
    void addEdge(int u, int v, double weight);
    // Method for getting the weight of an edge
    int getWeight(int u, int v);
    // Method for getting the number of vertices in the graph
    int getNumVertices();
    // Method for initializing matrix from file
    void setAdjacencyMatrix(vector<vector<double>>& matrix);
    // Method for printing contents of the matrix
    void print();
};


#endif //LISTA3_GRAPH_H
