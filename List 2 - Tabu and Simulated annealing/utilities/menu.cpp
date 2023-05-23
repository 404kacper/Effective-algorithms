#include "menu.h"

Menu::Menu() {
    readFileSelection();
    cout << "Wprowadz kryterium stopu [s]: \n";
    cin >> timeout;
    cout << "Wprowadz temperature poczatkowa (double): \n";
    cin >> temp;
    cout << "Wprowadz wspolczynnik obnizania temperatury (0-1): \n";
    cin >> alpha;
    cout << "Wprowadz wielkosc listy tabu (int): \n";
    cin >> tabu;

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

void Menu::solveTspWithSA() {
    long long int frequency, start, elapsed;
    SA sa(adjacencyMatrix, cities, timeout, temp, alpha);

    // Counting time
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = read_QPC();
    sa.solve();
    elapsed = read_QPC() - start;

    sa.printSolution();
    cout << "Czas [s] = " << fixed << setprecision(3) << (float)elapsed /frequency << endl;
    cout << "Czas [ms] = " << setprecision(0) << (1000.0 * elapsed) /frequency << endl;
    cout << "Czas [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;

    // Looping ot the same menu
    menuEngine(&firstMenu[0], firstMenuSize);
}

void Menu::solveTspWithTS() {
    long long int frequency, start, elapsed;
    TS ts(adjacencyMatrix, cities, timeout, tabu);

    // Counting time
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = read_QPC();
    ts.solve();
    elapsed = read_QPC() - start;

    ts.printSolution();
    cout << "Czas [s] = " << fixed << setprecision(3) << (float)elapsed /frequency << endl;
    cout << "Czas [ms] = " << setprecision(0) << (1000.0 * elapsed) /frequency << endl;
    cout << "Czas [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;

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

void Menu::readNewGraph() {
    readFileSelection();
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewTimeout() {
    cout << "Wprowadz kryterium stopu [s]:\n";
    cin >> timeout;
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewTemp() {
    cout << "Wprowadz temperature poczatkowa (double):\n";
    cin >> temp;
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewAlpha() {
    cout << "Wprowadz wspolczynnik obnizania temperatury (0-1):\n";
    cin >> alpha;
    menuEngine(&secondMenu[0], secondMenuSize);
}

void Menu::enterNewTabu() {
    cout << "Wprowadz wielkosc listy tabu (int):\n";
    cin >> tabu;
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
