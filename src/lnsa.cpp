#include <iostream>
#include <vector>
#include "greedy.h"
#include "tools.h"
#include "neighborhood.h"
#include "lnsa.h"

using namespace std;

Solution* lnsa (Instance& instance, int max_iter, int verbose, float p) {
    vector <int>* V;
    Greedy greedy = Greedy (&instance);
    Solution *sol, *best_sol = new Solution (instance.n);
    
    sol = greedy.initial_solution();
    while (reinsertion(*sol, sol->n, instance.v, instance.G) ||
           swap(*sol, sol->n, instance.v, instance.G));

    if (verbose)
        cout << "Initial solution = " << sol->obj << endl;

    best_sol->copy(*sol);
    for (int i = 0; i < max_iter; i++) {
        V = destroy_solution(*sol, p);
        greedy.greedy_solution(*sol, *V, V->size());

        while (reinsertion(*sol, sol->n, instance.v, instance.G) ||
               swap(*sol, sol->n, instance.v, instance.G));

        if (sol->obj < best_sol->obj) {
            best_sol->copy(*sol);

            if (verbose)
                cout << "Solution = " << best_sol->obj << endl;
        }
    }
    
    return best_sol;
}