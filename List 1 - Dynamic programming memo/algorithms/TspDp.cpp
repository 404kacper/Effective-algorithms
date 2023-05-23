#include "TspDp.h"

int TspDp::solve(int mask, int position) {
    int result = INT_MAX;

    if (mask == completedTour) {
        // return weight to starting vertex
        return memo[mask][position] = weights[position][0];
    }

    if (memo[mask][position] != -1) {
        return memo[mask][position];
    }

    for (int vertex = 0; vertex < cities; ++vertex) {
        // check if vertex was not visited (bitwise check for set bit at position of: vertex)
        // or in other words skip itself and visited vertices
        if ((mask&(1<<vertex))==0) {
            // calculate new distance recursively - changing the mask (which is just bitwise addition) accordingly with increasing vertex
            int newResult = weights[position][vertex] + solve(mask|(1<<vertex), vertex);
            result = min(result,newResult);
        }
    }

    return memo[mask][position] = result;
}

void TspDp::retrievePath() {
    int amountOfBitsSet = -1;
    int lastMask = 0;
    int currentBestMask = -1;
    int result = INT_MAX;

    // iterate through each of memo element cities times in order to build path for setting on bit for each iteration x = 0 - 0001; x = 1 - 0011; x = 2 - 0111
    for (int x = 0; x < cities; ++x) {
        for (int i = 0; i < memo.size(); ++i) {
            for (int j = 0; j < memo[0].size(); ++j) {
                if (memo[i][j] != -1) {
                    for (int k = 0; k < cities; ++k) {
                        if(((i&(1<<k))!=0))
                            amountOfBitsSet++;
                    }
                    // check only if masks match -> i - (bit at j position) == lastMask
                    // change lastMask only at the end of each x loop - mask only changes when we're changing position
                    // 1st we need to clear the currentMask from its bit and check if it's equal to last mask
                    int filteredMask = (i & ~(1 << j));
                    if ((amountOfBitsSet == x) && (filteredMask == lastMask)) {
                        int retrievedResult = memo[i][j];
                        int smaller = min(result, retrievedResult);
                        if (smaller == retrievedResult) {
                            result = retrievedResult;
                            // optimization so we don't have to loop through it in following iterations
//                            memo[i][j] = -1;
                            pathFromMemo[x] = j;
                            currentBestMask = i;
                        }
                    }
                    amountOfBitsSet = -1;
                }
            }
        }
        lastMask = currentBestMask;
    }
}

void TspDp::printMemo() {
    int amountOfBitsSet = 0;

    for (int x = 0; x <= cities; ++x) {
        for (int i = 0; i < memo.size(); ++i) {
            for (int j = 0; j < memo[0].size(); ++j) {
                if (memo[i][j] != -1) {
                    for (int k = 0; k < cities; ++k) {
                        if(((i&(1<<k))!=0))
                            amountOfBitsSet++;
                    }
                    if (amountOfBitsSet == x) {
                        cout << "Printing for " << x << " amount of bits" << endl;
                        bitset<5> mask(i);
                        int filteredMask = (i & ~(1 << j));
                        cout << "I: " << i << " J: " << j <<" Mask: " << mask << " Filtered mask: " << bitset<5>(filteredMask) << " Position: " << j << " Weight: " << memo[i][j] << endl;
                    }
                }
                amountOfBitsSet = 0;
            }
        }
        cout << endl;
    }

    for (int i = 0; i < pathFromMemo.size(); ++i) {
        cout << pathFromMemo[i] << " -> ";
    }
    cout << endl;
}

int TspDp::solveWithPath(int position, int mask) {
    int result = INT_MAX;
    vector<int> currentOptimalPath;

    if (mask == completedTour) {
        temp.clear();
        temp.push_back(position);

        // return weight to starting vertex
        return weights[position][0];
    }

    if (memo[mask][position] != -1) {
        temp.clear();
        temp = memoPaths[mask][position];
        return memo[mask][position];
    }

    for (int vertex = 0; vertex < cities; ++vertex) {
        // check if vertex was not visited (bitwise check for set bit at position of: vertex)
        // or in other words skip itself and visited vertices
        if ((mask&(1<<vertex))==0) {
            // calculate new distance recursively - changing the mask (which is just bitwise addition) accordingly with increasing vertex
            int newResult = weights[position][vertex] + solveWithPath(vertex,mask|(1<<vertex));
            temp.push_back(position);
            if (min(result, newResult) == newResult) {
                currentOptimalPath = temp;
            }
            result = min(result, newResult);
        }
    }

    temp = optimalPath = currentOptimalPath;
    memoPaths[mask][position] = temp;
    return memo[mask][position] = result;
}

vector<vector<int>> &TspDp::getWeights() const {
    return weights;
}

const vector<int> &TspDp::getOptimalPath() const {
    return optimalPath;
}
