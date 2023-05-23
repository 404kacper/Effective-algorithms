#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "Graph.h"
#include "Chromosome.h"
using namespace std;

// Class for implementing the genetic algorithm
class GeneticAlgorithm {
private:
    vector<Chromosome> population; // Population of chromosomes
    int populationSize; // Size of the population
    double mutationRate; // Mutation rate (probability of a gene being mutated)
    Graph graph; // Graph representing the problem
public:
    // Constructor for creating an instance of the genetic algorithm
    GeneticAlgorithm(int populationSize, double mutationRate, vector<vector<double>> matrix) {
        this->populationSize = populationSize;
        this->mutationRate = mutationRate;
        this->graph.setAdjacencyMatrix(matrix);
        // Create a random population of chromosomes
        for (int i = 0; i < populationSize; i++) {
            Chromosome chromosome(graph.getNumVertices());
            population.push_back(chromosome);
        }
    }
// Method for setting the fitness of all chromosomes in the population
    void setFitness() {
        for (int i = 0; i < populationSize; i++) {
            population[i].setFitness(graph);
        }
    }
// Method for getting the fittest chromosome in the population
    Chromosome getFittest() {
        int maxFitness = INT_MIN;
        int maxFitnessIndex = 0;
        for (int i = 0; i < populationSize; i++) {
            if (population[i].getFitness() > maxFitness) {
                maxFitness = population[i].getFitness();
                maxFitnessIndex = i;
            }
        }
        return population[maxFitnessIndex];
    }
// Method for getting the second fittest chromosome in the population
    Chromosome getSecondFittest() {
        int maxFitness1 = INT_MIN;
        int maxFitness2 = INT_MIN;
        int maxFitnessIndex1 = 0;
        int maxFitnessIndex2 = 0;
        for (int i = 0; i < populationSize; i++) {
            if (population[i].getFitness() > maxFitness1) {
                maxFitness2 = maxFitness1;
                maxFitness1 = population[i].getFitness();
                maxFitnessIndex2 = maxFitnessIndex1;
                maxFitnessIndex1 = i;
            } else if (population[i].getFitness() > maxFitness2) {
                maxFitness2 = population[i].getFitness();
                maxFitnessIndex2 = i;
            }
        }
        return population[maxFitnessIndex2];
    }
// Method for performing crossover on two randomly selected chromosomes
    void crossover() {
        int randIndex1 = rand() % populationSize;
        int randIndex2 = rand() % populationSize;
        Chromosome parent1 = population[randIndex1];
        Chromosome parent2 = population[randIndex2];
        vector<int> childGene1, childGene2;
        int randCrossoverPoint = rand() % parent1.getGene().size();
// Creating the first child by combining the genes of the two parents at a random crossover point
        for (int i = 0; i < randCrossoverPoint; i++) {
            childGene1.push_back(parent1.getGene()[i]);
        }
        for (int i = randCrossoverPoint; i < parent2.getGene().size(); i++) {
            childGene1.push_back(parent2.getGene()[i]);
        }
// Creating the second child by combining the genes of the two parents at the same random crossover point
        for (int i = 0; i < randCrossoverPoint; i++) {
            childGene2.push_back(parent2.getGene()[i]);
        }
        for (int i = randCrossoverPoint; i < parent1.getGene().size(); i++) {
            childGene2.push_back(parent1.getGene()[i]);
        }
        Chromosome child1(childGene1);
        Chromosome child2(childGene2);
        population[randIndex1] = child1;
        population[randIndex2] = child2;
    }
// Method for mutating a random gene of a random chromosome with a given mutation rate
    void mutate() {
        for (int i = 0; i < populationSize; i++) {
            double randMutation = (double) rand() / RAND_MAX;
            if (randMutation < mutationRate) {
                int randIndex1 = rand() % population[i].getGene().size();
                int randIndex2 = rand() % population[i].getGene().size();
                int temp = population[i].getGene()[randIndex1];
                population[i].getGene()[randIndex1] = population[i].getGene()[randIndex2];
                population[i].getGene()[randIndex2] = temp;
            }
        }
    }
// Method for evolving the population by selecting the fittest chromosomes, performing crossover, and mutation
    void evolveRouletteWheel() {
        Chromosome fittest = getFittest();
        Chromosome secondFittest = getSecondFittest();
        crossover();
        mutate();
        population[0] = fittest;
        population[1] = secondFittest;
    }
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 1);
    graph.addEdge(0, 3, 3);
    graph.addEdge(1, 2, 4);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 6);
    GeneticAlgorithm ga(10, 0.01, graph);
    for (int i = 0; i < 100; i++) {
        ga.setFitness();
        ga.evolve();
    }
    Chromosome fittest = ga.getFittest();
    cout << "Fittest chromosome: ";
    for (int i; i < fittest.getGene().size(); i++) {
        cout << fittest.getGene()[i] << " ";
    }
    cout << "\nFitness: " << fittest.getFitness() << endl;
    return 0;
}
