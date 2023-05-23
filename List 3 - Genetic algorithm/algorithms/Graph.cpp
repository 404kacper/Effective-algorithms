#include "Graph.h"

void Graph::addEdge(int u, int v, double weight) {
    adjacencyMatrix[u][v] = weight;
    adjacencyMatrix[v][u] = weight;
}

int Graph::getWeight(int u, int v) {
    return adjacencyMatrix[u][v];
}

int Graph::getNumVertices() {
    return adjacencyMatrix.size();
}

void Graph::setAdjacencyMatrix(vector<vector<double>> &matrix) {
    adjacencyMatrix = matrix;
}

void Graph::print() {
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        for (int j = 0; j < adjacencyMatrix[0].size(); ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}