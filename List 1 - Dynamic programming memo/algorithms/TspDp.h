#ifndef LISTA1_TSPDP_H
#define LISTA1_TSPDP_H

#include "vector"
#include "iostream"
#include <bitset>
#include "cmath"
using namespace std;

class TspDp {
private:
    vector<vector<int>>& weights;
    vector<vector<int>> memo;
    vector<vector<vector<int>>> memoPaths;
    vector<int> temp;
    vector<int> optimalPath;
    vector<int> pathFromMemo;
public:
    const vector<int> &getPathFromMemo() const;

private:
    int cities;
    int completedTour;
public:
    TspDp(vector<vector<int>>& matrix) : weights(matrix) {
    cities = weights.size();
    completedTour = (1<<cities) - 1;
    memo = vector<vector<int>> (pow(2,cities), vector<int> (cities, -1));
    pathFromMemo = vector<int>(cities,-1);
    memoPaths = vector<vector<vector<int>>> (pow(2,cities), vector<vector<int>>(cities, vector<int>(1,{})));
    };
    int solve(int mask, int position);
    int solveWithPath(int position, int mask);
    void retrievePath();
    void printMemo();
    const vector<int> &getOptimalPath() const;
    vector<vector<int>> &getWeights() const;
};


#endif //LISTA1_TSPDP_H
