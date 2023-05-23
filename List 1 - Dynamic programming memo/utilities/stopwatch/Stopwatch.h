#ifndef LISTA1_STOPWATCH_H
#define LISTA1_STOPWATCH_H

#include <random>
#include <ctime>
#include "windows.h"
#include "iostream"
#include "iomanip"
#include "../AdjacencyMatrix.h"

using namespace std;

class Stopwatch {

public:
    void start() {
        long long int frequency, start, elapsed;
        int sampleCount = 100;
        vector<int> N = {3,5,6,8,9,10,11,12,13,15,17,19,20,21};
        vector <double> averages (N.size(), 0);

        for (int i = 0; i < N.size(); ++i) {
            for (int j = 0; j < sampleCount; ++j) {
                // Generating variables for the problem
                AdjacencyMatrix cities = AdjacencyMatrix();
                cities.initializeMatrix(N[i]);
                generateGraph(cities, 1, 100);
                TspDp tspDp = TspDp(cities.getMatrix());

                // Counting time
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();
                tspDp.solveWithPath(1,0);
                elapsed = read_QPC() - start;
                // Storing elapsed time in microseconds
                averages[i] += (1000000.0* elapsed)/frequency;
            }
            // Calculating average
            averages[i] = averages[i]/sampleCount;
        }

        // Printing results
        cout << endl << "Tabela wynikow dla problemu TSP DP: " << endl << endl;
        for (int i = 0; i < averages.size(); ++i) {
            cout << "Usredniony czas [us] dla " << N[i] << " wierzcholkow: " << averages[i] << endl << endl;
        }
        system("PAUSE");
    }

    void measureTimeForUser(TspDp& tsp) {
        long long int frequency, start, elapsed;
        int weight;

        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

        start = read_QPC();
        weight = tsp.solveWithPath(0,1);
        elapsed = read_QPC() - start;

        cout << endl << "Waga sciezki = " << weight << endl;
        cout << "Czas kompilacji [us] = " << (1000000.0 * elapsed) / frequency << endl;

        cout << "0 -> ";
        int prev = 0;
        int sum = tsp.getWeights()[prev][prev];

        for (int i = 0; i < tsp.getOptimalPath().size(); ++i) {
            int v = tsp.getOptimalPath()[i];
            if (i == tsp.getOptimalPath().size()-1) {
                cout << v;
            } else {
                cout << v << " -> ";
            }
            sum += tsp.getWeights()[prev][v];
            prev = v;
        }
        cout << " : (waga ze sprawdzenia - " << sum << ")" << endl << endl;
    }

    void measureTimeForUserWithoutPath(TspDp& tsp) {
        long long int frequency, start, elapsed;
        int weight;

        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

        tsp.solve(1, 0);
        tsp.retrievePath();
        tsp.printMemo();

        start = read_QPC();
        weight = tsp.solve(1,0);
        tsp.retrievePath();
        elapsed = read_QPC() - start;

        cout << endl << "Waga sciezki = " << weight << endl;
        cout << "Czas kompilacji [us] = " << (1000000.0 * elapsed) / frequency << endl << endl;
    };

private:
    long long int read_QPC() {
        LARGE_INTEGER count;

        QueryPerformanceCounter(&count);
        return ((long long int)count.QuadPart);
    }

    void generateGraph(AdjacencyMatrix& matrix, int startRange, int endRange) {
        default_random_engine defEngine(time(0));
        uniform_int_distribution<int> weightsDistro(startRange, endRange);

        int dimensions = matrix.getMatrix().size();
        for (int i = 0; i < dimensions; ++i) {
            for (int j = 0; j < dimensions; ++j) {
                matrix.getMatrix()[i][j] = weightsDistro(defEngine);
            }
        }

        for (int i = 0; i < dimensions; ++i) {
            for (int j = 0; j < dimensions; ++j) {
                if (i == j) {
                    matrix.getMatrix()[i][j] = 0;
                }
            }
        }
    }
};
#endif //LISTA1_STOPWATCH_H
