#include "Chromosome.h"

vector<int> Chromosome::getGene() {
    return gene;
}

void Chromosome::setGene(vector<int> newGene) {
    gene = newGene;
}

void Chromosome::setFitness(Graph &graph) {
    fitness = 0;
    for (int i = 0; i < gene.size()-1; i++) {
        fitness += graph.getWeight(gene[i], gene[i+1]);
    }

    // Add the distance from last vertex in path to the initial vertex
    fitness += graph.getWeight(gene[graph.getNumVertices()-1], gene[0]);
}

int Chromosome::getFitness() {
    return fitness;
}

string Chromosome::getGeneAsString() {
    string geneString;
    for (auto const &i : gene) {
        geneString += to_string(i);
    }
    return geneString;
}