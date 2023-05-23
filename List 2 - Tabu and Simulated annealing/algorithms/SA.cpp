#include "SA.h"

double SA::calc_length() {
    double length = 0;
    for (int i = 0; i < N-1; i++) {
        length += d[path[i]][path[i+1]];
    }
    length += d[path[N-1]][path[0]];
    return length;
}

void SA::swap(int i, int j) {
    int temp = path[i];
    path[i] = path[j];
    path[j] = temp;
}

void SA::solve() {
    // Initialize random seed
    srand(time(0));

    // Initialize path to be the integers from 0 to N-1
    for (int i = 0; i < N; i++) {
        path.push_back(i);
    }

    // Initialize temperature
    double T = T0;

    // Get the current time for loop termination
    const auto start_time = chrono::steady_clock::now();

    while(true) {
        if (chrono::steady_clock::now() - start_time > M) {
            break;  // exit the loop
        }
        // Select two random cities to swap
        int i = rand() % N;
        int j = rand() % N;
        while (i == j) {
            j = rand() % N;
        }

        // Calculate the change in length
        double old_length = calc_length();
        swap(i, j);
        double new_length = calc_length();
        double delta = new_length - old_length;

        // If the new path is shorter, or if it is longer but still accepted
        // according to the probability function, then accept the new path
        if (delta < 0 || exp(-delta / T) > (double) rand() / RAND_MAX) {
            if (new_length < best_length) {
                best_length = new_length;
                for (int k = 0; k < N; k++) {
                    best_path[k] = path[k];
                }
            }
        }

        // Decrease the temperature
        T *= alpha;

    }
}

void SA::printSolution() {
    cout << "Najlepsza sciezka: ";
    for (int i = 0; i < N; ++i) {
        if (i != N-1)
            cout << best_path[i] << "->";
        else
            cout << best_path[i];

    }
    cout << "\nDlugosc: " << best_length << endl;
}