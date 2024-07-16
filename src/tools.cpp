#include <random>
#include "tools.h"

using namespace std;

vector <int>* destroy_solution (Solution& sol, float p) {
    vector <int>* V = new vector <int>();

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    int bin = 0;
    while (bin < sol.n)
        if (dis(gen) > p)
            bin++;
        else
            sol.reloc_bin(bin, V);

    return V;
}