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
#include "../algorithms/SA.h"
#include "../algorithms/TS.h"
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
    MenuItem firstMenu[4] = {
            {1, "Wyswietl macierz sasiedztwa.", &Menu::displayMatrix},
            {2, "Znajdz rozwiazanie tsp - SA.", &Menu::solveTspWithSA},
            {3, "Znajdz rozwiazanie tsp - TS.", &Menu::solveTspWithTS},
            {4, "Zmien wybrane parametry.",&Menu::changeParameters}
    };

    MenuItem secondMenu[6] = {
            {1, "Wczytaj nowy graf.", &Menu::readNewGraph},
            {2, "Wprowadz nowe kryterium stopu.", &Menu::enterNewTimeout},
            {3, "Wprowadz nowa temperature poczatkowa.", &Menu::enterNewTemp},
            {4, "Wprowadz nowy wspolczynnik obnizania temperatury.", &Menu::enterNewAlpha},
            {5, "Wprowadz nowy rozmiar listy tabu.", &Menu::enterNewTabu},
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
    double temp;
    double alpha;
    int tabu;

    // menu functions
    void menuEngine(MenuItem * pMenu, int itemQuantity);
    void readFileSelection();
    void solveTspWithSA();
    void solveTspWithTS();
    void displayMatrix();
    void changeParameters();
    void readNewGraph();
    void enterNewTimeout();
    void enterNewTemp();
    void enterNewAlpha();
    void enterNewTabu();
    void returnToFirstMenu();

    long long int read_QPC();
};
#endif //LISTA2_MENU_H
