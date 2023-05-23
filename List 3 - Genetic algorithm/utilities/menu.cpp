#include "menu.h"

Menu::Menu() {
    readFileSelection();
    cout << "Wprowadz kryterium stopu [s]: \n";
    cin >> timeout;
    cout << "Wprowadz wielkosc populacji poczatkowej (int): \n";
    cin >> initialPopulation;
    while (initialPopulation % 2 != 0) {
        cout << "Aby zachowac roznorodnosc populacji jej liczba musi byc parzysta - dwa geny rodzicow tworza dwa geny dzieci \n";
        cout << "Wprowadz ponownie wielkosc populacji poczatkowej (int): \n";
        cin >> initialPopulation;
    }
    cout << "Wprowadz wspolczynnik mutacji (0-1): \n";
    cin >> mutation;
    cout << "Wprowadz wspolczynnik krzyzowania (0-1): \n";
    cin >> crossing;

    // Transition to next menu
    menuEngine(&firstMenu[0], firstMenuSize);
}

void Menu::menuEngine(MenuItem *pMenu, int itemQuantity) {
    for (int i = 0; i < itemQuantity; ++i) {
        cout << pMenu[i].number << ". " << pMenu[i].text << endl;
    }
    cout << "Wybierz operacje: \n";
    int selection, i;
    cin >> selection;
    for (i = 0; i < itemQuantity; ++i) {
        if (selection==pMenu[i].number) {
            (this->*(pMenu[i].funcPtr))();
            break;
        }
    }
    if (i >= itemQuantity) {
        cout << "Wybierz poprawny numer z menu." << endl;
        menuEngine(pMenu, itemQuantity);
    }
}

void Menu::readFileSelection() {
    cout << "Wprowadz nazwe pliku (bez rozszerzenia): \n";
    string fileName;
    cin >> fileName;
    fileName = fileName + ".txt";

    // Reading and filling of graph
    FileReader reader = FileReader(fileName, adjacencyMatrix, cities);
    reader.readFile();
}

void Menu::solveTspWithGA() {
    long long int frequency, start, elapsed;
    GeneticAlgorithm ga(initialPopulation, mutation, crossing, timeout, adjacencyMatrix, crossingType);

    // Counting time
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    // Get the current time for loop termination
    start = read_QPC();
    // Iterate for the specified number of iterations
    ga.simulate();
    elapsed = read_QPC() - start;

    Chromosome fittest = ga.getFittest();
    cout << "Najlepsza sciezka: ";
    for (int i = 0; i < fittest.getGene().size(); i++) {
        cout << fittest.getGene()[i] << " ";
    }
    cout << "\nWaga sciezki: " << fittest.getFitness() << endl;

    cout << "Czas [s] = " << fixed << setprecision(3) << (float)elapsed /frequency << endl;
    cout << "Czas [ms] = " << setprecision(0) << (1000.0 * elapsed) /frequency << endl;
    cout << "Czas [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;

    // Looping ot the same menu
    menuEngine(&firstMenu[0], firstMenuSize);
}

void Menu::generateResults() {
    GeneticAlgorithm gaAuto(initialPopulation, mutation, crossing, timeout, adjacencyMatrix, crossingType);
    double interval, stopTime,totalNano;
    long long int frequency, start, elapsed;

    cout << "Wprowdz czas symulacji: " << endl;
    cin >> stopTime;
    cout << "Wprowadz interwaly wyswietlania wynikow w sekundach" << endl;
    cin >> interval;

    gaAuto.setFitness();
    cout << "Najlepszy osobnik z poczatkowej populacji: " << endl;
    for (int j = 0; j < gaAuto.getFittest().getGene().size(); ++j) {
        cout << gaAuto.getFittest().getGene()[j] << "->";
    }
    cout << "Oraz jego waga: " << gaAuto.getFittest().getFitness() << endl;

    double stopTimeNano = 1000000.0*stopTime;

    // Counting time
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

    double prevIntervalRes = 0;

    cout << "Kolejne najlepsze osobniki z populacji " << endl;

    while (totalNano < stopTimeNano) {
        start = read_QPC();
        gaAuto.setFitness();
        gaAuto.evolve();
        elapsed = read_QPC() - start;
        totalNano += (double)(1000000.0*elapsed/frequency);
        double intervalResult = totalNano/(1000000.0*interval);
        double doubleModuloInterval = fmod(intervalResult, interval);
        if (prevIntervalRes > doubleModuloInterval) {
            Chromosome fittest = gaAuto.getFittest();
            cout << "Wyniki po " << setprecision(2)<<intervalResult << " sekund: \n";
            for (int j = 0; j < fittest.getGene().size(); ++j) {
                cout << fittest.getGene()[j] << "->";
            }
            cout << "Oraz jego waga: " << gaAuto.getFittest().getFitness() << endl;
        }
        prevIntervalRes = doubleModuloInterval;

    }

    // Looping ot the same menu
    menuEngine(&firstMenu[0], firstMenuSize);
}


void Menu::displayMatrix() {
    cout << "Aktualana macierz to: " << endl;
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        for (int j = 0; j < adjacencyMatrix[0].size(); ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Looping to the same menu
    menuEngine(&firstMenu[0], firstMenuSize);
}

void Menu::changeParameters() {
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::changeCrossing() {
    cout << "Zmieniono sposob krzyzowania w populacji na: ";
    crossingType = !crossingType;
    if (crossingType) {
        cout << "Krzyzowanie permutacyjne." << endl;
    } else {
        cout << "Krzyzowanie jednopunktowe." << endl;
    }

    menuEngine(&firstMenu[0], firstMenuSize);
}

void Menu::readNewGraph() {
    readFileSelection();
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewTimeout() {
    cout << "Wprowadz kryterium stopu [s]:\n";
    cin >> timeout;
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewPopulation() {
    // TODO list
    //  - population can only be even number - add re-prompting here
    cout << "Wprowadz wielkosc populacji poczatkowej (int):\n";
    cin >> initialPopulation;
    while (initialPopulation % 2 != 0) {
        cout << "Aby zachowac roznorodnosc populacji jej liczba musi byc parzysta - dwa geny rodzicow tworza dwa geny dzieci \n";
        cout << "Wprowadz ponownie wielkosc populacji poczatkowej (int): \n";
        cin >> initialPopulation;
    }
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewMutation() {
    cout << "Wprowadz wspolczynnik mutacji (0-1):\n";
    cin >> mutation;
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewCrossing() {
    cout << "Wprowadz wspolczynnik krzyzowania (0-1):\n";
    cin >> crossing;
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::returnToFirstMenu() {
    menuEngine(&firstMenu[0], firstMenuSize);
}

long long int Menu::read_QPC() {
    LARGE_INTEGER count;

    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}
