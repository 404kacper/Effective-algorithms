#ifndef LISTA2_TS_H
#define LISTA2_TS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>

using namespace std;


class TS {
public:
    TS(vector<vector<double>>& passedCities, int amountOfCities, double numberOfSeconds, int tabuListSize) : numNodes(amountOfCities), T(tabuListSize)  {
        d = passedCities;
        M = chrono::duration<double> (numberOfSeconds);
    }
private:
    vector<vector<double>> d; // distance between cities
    vector<int> path; // current path
    vector<int> bestPath; // best path found so far
    chrono::duration<double> M; // number of seconds till termination
    const int T; // size of the tabu list
    int numNodes; // amount of cities
    double currentCost; // considered cost
    double bestCost; // best cost found so far
    // Function to compute cost of the current passedPath
    double computeCost(const vector<int>& passedPath, vector<vector<double>>& adjacencyMatrix);
    // Function generating a random and valid permutation of nodes
    vector<int> generateRandomPermutation();
    // Function implementing tabu search algorithm
public:
    void solve();
    void printSolution();
};


#endif //LISTA2_TS_H
