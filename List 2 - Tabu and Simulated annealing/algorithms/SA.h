#ifndef LISTA2_SA_H
#define LISTA2_SA_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

class SA {
public:
    SA(vector<vector<double>>& passedCities, int amountOfCities, double numberOfSeconds, double initialTemp, double tempDecay) : N(amountOfCities), T0(initialTemp), alpha(tempDecay)  {
        d = passedCities;
        M = chrono::duration<double> (numberOfSeconds);
    };
private:
    const int N; // number of cities
    chrono::duration<double> M;
    const double T0; // initial temperature
    const double alpha; // temperature decay rate
    vector<vector<double>> d; // distance between cities
    vector<int> path; // current path
    vector<int> best_path = vector<int> (N, -1); // best path found so far
    double best_length = 1e12; // length of best path

    // Calculates length of the current path
    double calc_length();
    // Swaps two cities in the path
    void swap(int i, int j);
public:
    // Main function
    void solve();
    // Print function
    void printSolution();
};


#endif //LISTA2_SA_H
