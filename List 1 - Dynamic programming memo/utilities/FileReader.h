#ifndef LISTA1_FILEREADER_H
#define LISTA1_FILEREADER_H

#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include "AdjacencyMatrix.h"


class FileReader {
private:
    string fileName;
    AdjacencyMatrix& weights;

public:
    FileReader(string fileName, AdjacencyMatrix& weights) : fileName(fileName), weights(weights) {};

    void readFile() {
        ifstream file(fileName);
        int cities, val;

        if(file.is_open()) {
            file >> cities;
            if(file.fail()) {
                cout << "File error - READ SIZE" << endl;
            } else {
                weights.initializeMatrix(cities);
                for(int i = 0; i < cities; i++) {
                    for (int j = 0; j < cities; ++j) {
                        file >> val;
                        if(file.fail()) {
                            cout << "File error - READ DATA" << endl;
                            break;
                        } else {
                            weights.getMatrix()[i][j] = val;
                        }
                    }
                }
                file.close();
            }

        } else {
            cout << "File error - OPEN" << endl;
        }
    }
};


#endif //LISTA1_FILEREADER_H
