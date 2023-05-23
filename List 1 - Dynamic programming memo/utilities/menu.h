// wygenerowane
#ifndef LISTA1_MENU_H
#define LISTA1_MENU_H

// biblioteki
#include "iostream"
#include <bitset>

// klasy programu
#include "../algorithms/TspDp.h"
#include "FileReader.h"
#include "stopwatch/Stopwatch.h"


typedef void (*MenuFuncPtr)();

struct MenuItem {
    int number;
    const char* text;
    MenuFuncPtr funcPtr;
};

void readFileSelection();
void displayMatrix();
void tspDpSolutionWithPath();
void tspDpSolutionWithoutPath();
void returnToStart();
void generateResults();


MenuItem firstMenu[] = {
        {1, "Wczytaj dane z pliku.", readFileSelection},
};

MenuItem secondMenu[] = {
        {2, "Wyswietl macierz sasiedztwa.",                                           displayMatrix},
        {3, "Znajdz rozwiazanie TSP DP.", tspDpSolutionWithPath},
        {4, "Znajdz szybsze rozwiazanie, ale bez sciezki.", tspDpSolutionWithoutPath},
        {5, "Generuj wyniki.",                                                         generateResults},
        {6, "Powrot do poczatku.",                                                     returnToStart}
};

int firstMenuSize = sizeof (firstMenu) / sizeof (firstMenu[0]);
int secondMenuSize = sizeof (secondMenu) / sizeof (secondMenu[0]);
AdjacencyMatrix adjacencyMatrix;

void menuEngine(MenuItem * pMenu, int itemQuantity) {
    for (int i = 0; i < itemQuantity; ++i) {
        cout << pMenu[i].number << ". " << pMenu[i].text << endl;
    }
    cout << "Wybierz operacje:";
    int selection, i;
    cin >> selection;
    for (i = 0; i < itemQuantity; ++i) {
        if (selection==pMenu[i].number) {
            (pMenu[i].funcPtr)();
            break;
        }
    }
    if (i >= itemQuantity) {
        cout << "Wybierz poprawny numer z menu." << endl;
        menuEngine(pMenu, itemQuantity);
    }
}

void readFileSelection() {
    cout << "Wprowadz nazwe pliku(domyslne rozszerzenie .txt): " << endl;
    string fileName;
    cin >> fileName;
    fileName = fileName + ".txt";

    // Creating empty graph
    adjacencyMatrix = AdjacencyMatrix();

    // Reading and filling of graph
    FileReader reader = FileReader(fileName, adjacencyMatrix);
    reader.readFile();

    // Transition to next menu
    menuEngine(&secondMenu[0], secondMenuSize);
}

void tspDpSolutionWithoutPath() {
    TspDp tsp = TspDp(adjacencyMatrix.getMatrix());
    Stopwatch st = Stopwatch();
    st.measureTimeForUserWithoutPath(tsp);

    // Looping ot the same menu
    menuEngine(&secondMenu[0], secondMenuSize);
}

void tspDpSolutionWithPath() {
    TspDp tsp = TspDp(adjacencyMatrix.getMatrix());
    Stopwatch st = Stopwatch();
    st.measureTimeForUser(tsp);

    // Looping ot the same menu
    menuEngine(&secondMenu[0], secondMenuSize);
}

void generateResults() {
    Stopwatch st1 = Stopwatch();
    st1.start();

    menuEngine(&secondMenu[0], secondMenuSize);
}

void displayMatrix() {
    adjacencyMatrix.print();

    // Looping to the same menu
    menuEngine(&secondMenu[0], secondMenuSize);
}

void returnToStart() {
    menuEngine(&firstMenu[0], firstMenuSize);

}

void Menu() {
    menuEngine(&firstMenu[0], firstMenuSize);
}

#endif //LISTA1_MENU_H
