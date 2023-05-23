#ifndef LISTA3_CHROMOSOME_H
#define LISTA3_CHROMOSOME_H

#include "vector"
#include "algorithm"
#include "Graph.h"
#include "random"
#include "chrono"

using namespace std;


class Chromosome {
private:
    vector<int> gene; // Representation of the solution (a permutation of the vertices)
    double fitness; // Fitness of the solution (total weight of edges in the tour)

public:
    Chromosome() {

    };

    // Constructor for creating a valid TSP solution using a nearest neighbor algorithm
    Chromosome(int numVertices, Graph &graph) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 rng(seed); // seed generator
        gene.resize(numVertices);
        uniform_int_distribution<> dis_index(0, numVertices-1);
        vector<bool> visited(numVertices, false);
        int current = dis_index(rng);
        gene[0] = current;
        visited[current] = true;
        for (int i = 1; i < numVertices; i++) {
            int next = 0;
            double minDistance = INT_MAX;
            for (int j = 0; j < numVertices; j++) {
                if (!visited[j] && graph.getWeight(current, j) < minDistance) {
                    next = j;
                    minDistance = graph.getWeight(current, j);
                }
            }
            gene[i] = next;
            visited[next] = true;
            current = next;
        }
    }
    // Constructor for creating a chromosome with a given gene
    Chromosome(vector<int> gene) {
        this->gene = gene;
    }
    // Method for getting the gene of the chromosome
    vector<int> getGene();
    // Method for setting the gene of the chromosome
    void setGene(vector<int> newGene);
    // Method for setting the fitness of the chromosome based on a given graph
    void setFitness(Graph &graph);
    // Method for getting the fitness of the chromosome
    int getFitness();
    // Method for getting the gene as a string
    string getGeneAsString();
};


#endif //LISTA3_CHROMOSOME_H
