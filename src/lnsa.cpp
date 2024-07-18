#include <iostream>
#include <vector>
#include "greedy.h"
#include "nghbr.h"
#include "tools.h"
#include "lnsa.h"

using namespace std;

Solution* lnsa (Instance& instance, int patience, int verbose, float p) {
    int iter;
    int*  v = instance.v;
    int** G = instance.G;

    vector <int>* V;
    Greedy greedy = Greedy (&instance);
    Solution *sol, *best = new Solution (instance.n);

    sol = greedy.initial_solution();
    while (search(*sol, sol->n, v, G));

    best->copy(*sol);
    if (verbose)
        cout << "Initial solution = " << best->obj << endl;

    iter = 0;
    while (iter <= patience) {
        V = destroy_solution(*sol, p);

        greedy.greedy_solution(*sol, *V, V->size());
        while (search(*sol, sol->n, v, G));

        if (sol->obj < best->obj) {
            iter = 0;

            best->copy(*sol);
            if (verbose)
                cout << "Solution = " << best->obj << endl;
        } else {
            iter++;
        }

        delete V;
    }

    delete sol;

    return best;
}