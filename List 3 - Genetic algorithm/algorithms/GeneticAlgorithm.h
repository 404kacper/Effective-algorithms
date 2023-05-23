#ifndef LISTA3_GENETICALGORITHM_H
#define LISTA3_GENETICALGORITHM_H

#include "Graph.h"
#include "Chromosome.h"
#include "chrono"
#include <unordered_set>
#include <random>

class GeneticAlgorithm {
private:
    vector<Chromosome> population; // Population of chromosomes
    unordered_set<string> visitedGene;
    int populationSize; // Size of the population
    double mutationRate; // Mutation rate (probability of a gene being mutated)
    double crossoverRate; // Crossover rate (probability of performing crossover)
    chrono::duration<double> M;
    Graph graph; // Graph representing the problem
//    random_device rd;  // generator
    uniform_real_distribution<double> dis_prob; // create a uniform distribution of probability between 0 and 1
    uniform_int_distribution<> dis_index; // create a uniform distribution of all available indexes in population
    int mutated = 0;
    int crossed = 0;
    bool isOrderCrossover;

public:
    // Constructor for creating an instance of the genetic algorithm
    GeneticAlgorithm(int populationSize, double mutationRate, double crossoverRate, double simulationTime, vector<vector<double>> matrix, bool crossingType) {
        this->populationSize = populationSize;
        this->mutationRate = mutationRate;
        this->crossoverRate = crossoverRate;
        this->graph.setAdjacencyMatrix(matrix);
        this->M = chrono::duration<double> (simulationTime);
        this->dis_prob = uniform_real_distribution<double> (0.0, 1.0);
        this->dis_index = uniform_int_distribution<> (0, populationSize-1);
        this->isOrderCrossover = crossingType;
        // Create a valid population (for TSP) of chromosomes
        for (int i = 0; i < populationSize; i++) {
            Chromosome chromosome(graph.getNumVertices(), graph);
            population.push_back(chromosome);
        }
    }
    // Method for setting the fitness of all chromosomes in the population
    void setFitness();
    // Method for getting the fittest chromosome in the population
    Chromosome getFittest();
    // Method for getting the second-fittest chromosome in the population
    Chromosome getSecondFittest();
    // Method for performing crossover on two selected chromosomes - one point crossover
    void crossover(Chromosome &offspring1, Chromosome &offspring2);
    // Different method for performing crossover on two selected chromosomes - order crossover - should introduce more diversity into algorithm
    void crossoverOX(Chromosome &offspring1, Chromosome &offspring2);
    // Method for mutating a random gene of a random chromosome with a given mutation rate - random gene replacement mutation
    void mutate(Chromosome &offspring1, Chromosome &offspring2);
    // Method to repair invalid chromosomes
    void repairChromosome(Chromosome &chromosome);
    // Method for creating unique chromosome in population
    void createNewChromosome(Chromosome& newChromosome);
    // Method for evolving the population by selecting the fittest chromosomes, performing crossover, and mutation - technique is roulette wheel selection (higher fitness selected more often)
    void evolve();
    // Method for running the algorithm with user variables - current version works only for undirected(symmetric) graphs
    void simulate();
};


#endif //LISTA3_GENETICALGORITHM_H
