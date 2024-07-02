#include <cstdlib>
#include "tools.h"

using namespace std;

vector <int>* destroy_solution (Solution& sol, float p) {
    int bin;
    double test;
    vector <int>* V = new vector <int>();
    
    bin = 0;
    while (bin < sol.n) {
        test = static_cast<double>(rand()) / RAND_MAX;

        if (test <= p) {
            for (int item : sol[bin]->items)
                V->push_back(item);

            sol.erase_bin(bin);
        } else {
            bin++;
        }
    }

    return V;
}