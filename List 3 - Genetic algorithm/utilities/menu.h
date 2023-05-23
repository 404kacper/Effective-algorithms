// generated
#ifndef LISTA2_MENU_H
#define LISTA2_MENU_H

// libraries
#include "iostream"
#include "iomanip"
#include "ctime"
#include "random"
#include "windows.h"
#include <future>
#include <chrono>

// programme classes
#include "../algorithms/GeneticAlgorithm.h"
#include "FileReader.h"

class Menu {
public:
    Menu();
private:
    // menu engine vars
    typedef void (Menu::*MenuFuncPtr)();
    struct MenuItem {
        int number;
        const char* text;
        MenuFuncPtr funcPtr;
    };

    // menu item arrays
    MenuItem firstMenu[5] = {
            {1, "Wyswietl macierz sasiedztwa.", &Menu::displayMatrix},
            {2, "Znajdz rozwiazanie tsp - GA.", &Menu::solveTspWithGA},
            {3, "Zmien wybrane parametry.",&Menu::changeParameters},
            {4, "Zmien sposob krzyzowania w populacji. ", &Menu::changeCrossing},
            {5, "Generuj wyniki", &Menu::generateResults}
    };

    MenuItem secondMenu[6] = {
            {1, "Wczytaj nowy graf.", &Menu::readNewGraph},
            {2, "Wprowadz nowe kryterium stopu.", &Menu::enterNewTimeout},
            {3, "Wprowadz nowa populacje poczatkowa.", &Menu::enterNewPopulation},
            {4, "Wprowadz nowy wspolczynnik mutacji.", &Menu::enterNewMutation},
            {5, "Wprowadz nowy wspolczynnik krzyzowania.", &Menu::enterNewCrossing},
            {6, "Powrot do rozwiazan.", &Menu::returnToFirstMenu}
    };

    // menu variables
    int firstMenuSize = sizeof (firstMenu) / sizeof (firstMenu[0]);
    int secondMenuSize = sizeof (secondMenu) / sizeof (secondMenu[0]);

    // read data
    vector<vector<double>> adjacencyMatrix;
    int cities;

    // algorithm variables
    double timeout;
    int initialPopulation;
    double mutation;
    double crossing;
    bool crossingType = 0;

    // menu functions
    void menuEngine(MenuItem * pMenu, int itemQuantity);
    void readFileSelection();
    void solveTspWithGA();
    void displayMatrix();
    void changeParameters();
    void readNewGraph();
    void changeCrossing();
    void generateResults();
    void enterNewTimeout();
    void enterNewPopulation();
    void enterNewMutation();
    void enterNewCrossing();
    void returnToFirstMenu();

    long long int read_QPC();
};
#endif //LISTA2_MENU_H
