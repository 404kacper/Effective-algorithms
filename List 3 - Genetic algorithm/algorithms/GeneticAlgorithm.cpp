#include "GeneticAlgorithm.h"

void GeneticAlgorithm::setFitness() {
    for (int i = 0; i < populationSize; i++) {
        population[i].setFitness(graph);
    }
}

Chromosome GeneticAlgorithm::getFittest() {
    int minFitness = INT_MAX;
    int minFitnessIndex = 0;

    for (int i = 0; i < populationSize; i++) {
        if (population[i].getFitness() < minFitness && i != minFitness) {
            minFitness = population[i].getFitness();
            minFitnessIndex = i;
        }
    }
    return population[minFitnessIndex];
}

Chromosome GeneticAlgorithm::getSecondFittest() {
    int minFitness1 = INT_MAX;
    int minFitness2 = INT_MAX;

    int minFitnessIndex1 = 0;
    int minFitnessIndex2 = 0;

    for (int i = 0; i < populationSize; i++) {
        if (population[i].getFitness() < minFitness1) {
            minFitness2 = minFitness1;
            minFitness1 = population[i].getFitness();
            minFitnessIndex2 = minFitnessIndex1;
            minFitnessIndex1 = i;
        } else if (population[i].getFitness() < minFitness2 && i != minFitnessIndex2) {
            minFitness2 = population[i].getFitness();
            minFitnessIndex2 = i;
        }
    }
    return population[minFitnessIndex2];
}

void GeneticAlgorithm::crossover(Chromosome &offspring1, Chromosome &offspring2) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed); // seed generator
    // Only perform crossover with a certain probability
    double randCrossover = dis_prob(gen);
    if (randCrossover > crossoverRate) {
        return;
    }
    crossed++;
    int randIndex1 = dis_index(gen);
    int randIndex2 = dis_index(gen);

    // Ensure that the two selected parents are unique
    while (randIndex1 == randIndex2) {
        randIndex2 = dis_index(gen);
    }

    Chromosome parent1 = population[randIndex1];
    uniform_int_distribution<> dis_crossoverPoint(0, parent1.getGene().size()-2); // create a uniform distribution of crossover point between 0 and parent1.getGene().size()-2
    Chromosome parent2 = population[randIndex2];

    vector<int> childGene1, childGene2;
    int randCrossoverPoint = dis_crossoverPoint(gen);
    // Ensure that the crossover point is not at the last gene
    if(randCrossoverPoint == parent1.getGene().size()-1) randCrossoverPoint--;
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
    offspring1 = child1;
    offspring2 = child2;
}

void GeneticAlgorithm::crossoverOX(Chromosome &offspring1, Chromosome &offspring2) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed); // seed generator
    // Only perform crossover with a certain probability
    double randCrossover = dis_prob(gen);
    if (randCrossover > crossoverRate) {
        return;
    }
    crossed++;
    int randIndex1 = dis_index(gen);
    int randIndex2 = dis_index(gen);

    // Ensure that the two selected parents are unique
    while (randIndex1 == randIndex2) {
        randIndex2 = dis_index(gen);
    }

    Chromosome parent1 = population[randIndex1];
    uniform_int_distribution<> dis_crossoverPoint(0, parent1.getGene().size()-2); // create a uniform distribution of crossover point between 0 and parent1.getGene().size()-2
    Chromosome parent2 = population[randIndex2];

    vector<int> childGene1, childGene2;

    int randCrossoverPoint1 = dis_crossoverPoint(gen);
    int randCrossoverPoint2 = dis_crossoverPoint(gen);

    while(randCrossoverPoint1==randCrossoverPoint2) randCrossoverPoint2 = dis_crossoverPoint(gen);

    if(randCrossoverPoint1>randCrossoverPoint2) swap(randCrossoverPoint1,randCrossoverPoint2);

    for(int i=randCrossoverPoint1;i<randCrossoverPoint2;i++)
    {
        childGene1.push_back(parent1.getGene()[i]);
        childGene2.push_back(parent2.getGene()[i]);
    }

    for(int i=0;i<randCrossoverPoint1;i++)
    {
        childGene1.push_back(parent2.getGene()[i]);
        childGene2.push_back(parent1.getGene()[i]);
    }

    for(int i=randCrossoverPoint2;i<parent1.getGene().size();i++)
    {
        childGene1.push_back(parent2.getGene()[i]);
        childGene2.push_back(parent1.getGene()[i]);
    }

    Chromosome child1(childGene1);
    Chromosome child2(childGene2);
    offspring1 = child1;
    offspring2 = child2;
}

void GeneticAlgorithm::mutate(Chromosome &offspring1, Chromosome &offspring2) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed); // seed generator
    // Only perform crossover with a certain probability
    double randMutation = dis_prob(gen);
    if (randMutation > mutationRate) {
        return;
    }
    mutated++;
    // Select random gene from population to swap with offspring
    int randIndex = dis_index(gen);
    Chromosome randomPopulationMember = population[randIndex];

    uniform_int_distribution<> dis_vertices(0, offspring1.getGene().size()-1); // create a uniform distribution of possible vertices

    // Select random gene from offspring to swap
    int randOffspringIndex1 = dis_vertices(gen);
    int randOffspringIndex2 = dis_vertices(gen);

    // Perform the gene swap
    int temp1 = offspring1.getGene()[randOffspringIndex1];
    offspring1.getGene()[randOffspringIndex1] = randomPopulationMember.getGene()[randOffspringIndex1];
    randomPopulationMember.getGene()[randOffspringIndex1] = temp1;

    int temp2 = offspring2.getGene()[randOffspringIndex2];
    offspring2.getGene()[randOffspringIndex2] = randomPopulationMember.getGene()[randOffspringIndex2];
    randomPopulationMember.getGene()[randOffspringIndex2] = temp2;
}

void GeneticAlgorithm::repairChromosome(Chromosome &chromosome) {
    vector<bool> visited(graph.getNumVertices(), false);
    vector<int> gene = chromosome.getGene();
    int tourLength = 0;
    // Loop through the gene
    for (int i = 0; i < gene.size(); i++) {
        // Check if the vertex has already been visited
        if (visited[gene[i]]) {
            // If it has, find the next unvisited vertex
            int nextVertex = 0;
            double minDistance = INT_MAX;
            for (int j = 0; j < graph.getNumVertices(); j++) {
                if (!visited[j] && graph.getWeight(gene[i], j) < minDistance && gene[i] != j) {
                    minDistance = graph.getWeight(gene[i], j);
                    nextVertex = j;
                }
            }
            // Replace the repeated vertex with the unvisited one
            gene[i] = nextVertex;
        }
        visited[gene[i]] = true;
        if (i < gene.size()-1) {
            tourLength += graph.getWeight(gene[i], gene[i+1]);
        }
    }
    chromosome.setGene(gene);
    chromosome.setFitness(graph);
}

void GeneticAlgorithm::createNewChromosome(Chromosome &newChromosome) {
    newChromosome = Chromosome(graph.getNumVertices(), graph);
    string gene = newChromosome.getGeneAsString();
    while(visitedGene.count(gene)){
        newChromosome = Chromosome(graph.getNumVertices(), graph);
        gene = newChromosome.getGeneAsString();
    }
    visitedGene.insert(gene);

}

void GeneticAlgorithm::evolve() {
    vector<Chromosome> newPopulation;
    // elitist selection part - preserves two optimal solutions in each population
    Chromosome fittest = getFittest();
    Chromosome secondFittest = getSecondFittest();
    // adding them to new population
    newPopulation.push_back(fittest);
    newPopulation.push_back(secondFittest);

    for (int i = 2; i < populationSize-1; i+=2) {
        Chromosome offspring1(population[i].getGene());
        Chromosome offspring2(population[i+1].getGene());
        if (isOrderCrossover) {
            crossoverOX(offspring1, offspring2);
        } else {
            crossover(offspring1, offspring2);
        }
        repairChromosome(offspring1);
        repairChromosome(offspring2);
        mutate(offspring1, offspring2);
        repairChromosome(offspring1);
        repairChromosome(offspring2);
        newPopulation.push_back(offspring1);
        newPopulation.push_back(offspring2);
    }
//    cout << "New loop" << endl;
//
//    cout << "Amount of mutated individuals in population: " << mutated << " and crossed ones: " << crossed << endl;
//    mutated = 0;
//    crossed = 0;
//
//    for (int i = 0; i < newPopulation.size(); ++i) {
//        cout << "Individual number  " << i << " has gene: ";
//        for (int j = 0; j < newPopulation[0].getGene().size(); ++j) {
//            cout << newPopulation[i].getGene()[j] << "->";
//        }
//
//        cout << " Gene " << i << " fitness " << newPopulation[i].getFitness() << endl;
//    }
    population = newPopulation;
}

void GeneticAlgorithm::simulate() {
    const auto start_time = chrono::steady_clock::now();

//    int x = 0;
    // Iterate for the specified number of iterations
    while (true) {
        if (chrono::steady_clock::now() - start_time > M) {
            break;  // exit the loop
        }
        this->setFitness();
//        if (x == 0)
//        {
//            cout << "Initial population" << endl;
//            for (int i = 0; i < population.size(); ++i) {
//                cout << "Individual number  " << i << " has gene: ";
//                for (int j = 0; j < population[0].getGene().size(); ++j) {
//                    cout << population[i].getGene()[j] << "->";
//                }
//
//                cout << " Gene " << i << " fitness " << population[i].getFitness() << endl;
//            }
//            x = 1;
//        }
        this->evolve();
    }
}