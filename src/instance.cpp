#include <iostream>
#include <fstream>
#include <sstream>
#include "instance.h"
#include "constants.h"

using namespace std;

// Reading an instance from a file
Instance::Instance (char* filename) {
    int v1, v2;
    string line;
    ifstream file(filename);

    file >> n;

    v = new int[n];
    G = new int*[n];
    for (int i = 0; i < n; i++)
        G[i] = new int[n]();
    
    // Getting the following data:
    // Weight of items
    // Incompatibilities between items
    while (getline(file, line)) {
        istringstream iss(line);

        iss >> v1;
        v1--;
        iss >> v[v1];

        while (iss >> v2)
            G[v1][v2-1] = G[v2-1][v1] = 1;
    }

    // Extended conflict graph
    for (v1 = 0; v1 < n-1; v1++)
        for (v2 = v1+1; v2 < n; v2++)
            if (v[v1] + v[v2] > MAX_COST)
                G[v1][v2] = G[v2][v1] = 1;

    file.close();
}

// Printing the instance description
void Instance::describe () {
    cout << "Number of items = " << n << endl;

    cout << "v = [ ";
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << "]" << endl;

    cout << "L =" << endl;
    for (int i = 0; i < n; i++) {
        cout << "    ";
        for (int j = 0; j < n; j++)
            cout << G[i][j] << " ";
        cout << endl;
    }
}