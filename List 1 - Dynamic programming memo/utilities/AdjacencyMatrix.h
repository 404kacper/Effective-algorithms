#ifndef LISTA1_ADJACENCYMATRIX_H
#define LISTA1_ADJACENCYMATRIX_H

#include <vector>
#include "iostream"

using namespace std;


class AdjacencyMatrix {
    vector<vector<int>> matrix;
    int size;

public:
    AdjacencyMatrix() : matrix({}) {
    }
    // Changes weight of a given edge
    void modifyEdge(int from, int to, int weight);
    // Intializes matrix of amountOfCities X amountOfCites size with 0 values
    void initializeMatrix(int amountOfCities);
    // Returns reference to the matrix member
    vector<vector<int>> &getMatrix();
    // Displays matrix
    void print();
};


#endif //LISTA1_ADJACENCYMATRIX_H
