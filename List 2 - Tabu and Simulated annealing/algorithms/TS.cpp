#include "TS.h"

double TS::computeCost(const vector<int>& passedPath, vector<vector<double>>& adjacencyMatrix)
{
    double cost = 0;
    for (int i = 0; i < passedPath.size() - 1; i++)
    {
        cost += adjacencyMatrix[passedPath[i]][passedPath[i + 1]];
    }
    cost += adjacencyMatrix[passedPath[passedPath.size() - 1]][passedPath[0]];
    return cost;
}

vector<int> TS::generateRandomPermutation()
{
    // Create a vector with the nodes in order
    vector<int> permutation(numNodes);
    for (int i = 0; i < numNodes; i++)
    {
        permutation[i] = i;
    }

    // Shuffle the vector using the current time as a seed for the random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(permutation.begin(), permutation.end(), default_random_engine(seed));

    return permutation;
}

void TS::solve()
{
    // Initialize the current path to a random valid permutation of the nodes
    path = generateRandomPermutation();
    currentCost = computeCost(path, d);

    // Initialize the best path and cost to the current path and cost
    bestPath = path;
    bestCost = currentCost;

    // Create the tabu list as a queue of the last "tabuListSize" moves made
    deque<pair<int, int>> tabuList;

    // Get the current time for loop termination
    const auto start_time = chrono::steady_clock::now();

    // Iterate for the specified number of iterations
    while (true)
    {
        if (chrono::steady_clock::now() - start_time > M) {
            break;  // exit the loop
        }
        // Initialize the best neighbor to the current path
        vector<int> bestNeighbor = path;
        double bestNeighborCost = currentCost;
        int j_swap = -1, k_swap = -1;

        // Try moving each node to a different position in the path
        for (int j = 0; j < numNodes; j++)
        {
            for (int k = j + 1; k < numNodes; k++)
            {
                // Create a copy of the current path
                vector<int> neighbor = path;

                // Swap positions jth and kth nodes in the path
                swap(neighbor[j], neighbor[k]);

                // Compute the cost of the neighbor
                double neighborCost = computeCost(neighbor, d);

                // If neighbor is better than current best neighbor, and move is not tabu - update the best neighbor
                if (neighborCost < bestNeighborCost && find(tabuList.begin(), tabuList.end(), make_pair(j, k)) == tabuList.end())
                {
                    bestNeighbor = neighbor;
                    bestNeighborCost = neighborCost;
                    j_swap = j;
                    k_swap = k;
                }
            }
        }

        // Update the current path and cost to the best neighbor
        path = bestNeighbor;
        currentCost = bestNeighborCost;

        // Update the tabu list by adding the move made to the end of the queue and removing the oldest move from the front
        tabuList.push_back(make_pair(j_swap,k_swap));
        if (tabuList.size() > T)
        {
            tabuList.pop_front();
        }

        // Update the best path and cost if the current path is better
        if (currentCost < bestCost)
        {
            bestPath = path;
            bestCost = currentCost;
        }
    }
}

void TS::printSolution() {
    cout << "Najlepsza sciezka: ";
    for (int i = 0; i < bestPath.size(); ++i) {
        if (i != bestPath.size()-1)
            cout << bestPath[i] << "->";
        else
            cout << bestPath[i] << endl;

    }
    cout << "Dlugosc: " << computeCost(bestPath, d) << endl;
}
