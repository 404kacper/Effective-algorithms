#ifndef LISTA2_FILEREADER_H
#define LISTA2_FILEREADER_H

#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include "vector"
#include "iostream"

using namespace std;

class FileReader {
private:
    string fileName;
    vector<vector<double>>& weights;
    int& cities;

public:
    FileReader(string fileName, vector<vector<double>>& weights, int& passedCitiesVar) : fileName(fileName), weights(weights),  cities(passedCitiesVar){};

    void readFile() {
        ifstream file(fileName);
        double val;

        if(file.is_open()) {
            file >> cities;
            if(file.fail()) {
                cout << "File error - READ SIZE" << endl;
            } else {
                weights = vector<vector<double>> (cities, vector<double> (cities, 0));
                for(int i = 0; i < cities; i++) {
                    for (int j = 0; j < cities; ++j) {
                        file >> val;
                        if(file.fail()) {
                            cout << "File error - READ DATA" << endl;
                            break;
                        } else {
                            weights[i][j] = val;
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


#endif //LISTA2_FILEREADER_H
