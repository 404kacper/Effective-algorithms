#include "AdjacencyMatrix.h"


void AdjacencyMatrix::modifyEdge(int from, int to, int weight) {
    matrix[from][to] = weight;
}

void AdjacencyMatrix::initializeMatrix(int amountOfCities) {
    matrix = vector<vector<int>> (amountOfCities, vector<int> (amountOfCities, 0));
}


vector<vector<int>> &AdjacencyMatrix::getMatrix() {
    return matrix;
}

void AdjacencyMatrix::print() {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

