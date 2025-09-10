#include <iostream>
#include <vector>
#include "greedy.h"
#include "neighborhood.h"
#include "destroy.h"
#include "lnsa.h"
#include "constants.h"

using namespace std;

Solution lnsa (Instance& instance, int patience, float p, GreedyChooser g, int verbose) {
    Greedy   greedy = Greedy (instance, BIN_TYPES, BIN_SIZE, g);
    Solution sol    = greedy.initial_solution();

    while (search(sol, instance));

    Solution best = sol;
    if (verbose)
        cout << "Initial solution = " << best.get_obj() << endl;

    int iter = 0;
    while (iter <= patience) {
        vector <int> V = destroy_solution(sol, p);

        greedy.greedy_solution(sol, V);
        while  (search(sol, instance));

        if (sol.get_obj() < best.get_obj()) {
            iter =   0;
            best = sol;

            if (verbose)
                cout << "Solution = " << best.get_obj() << endl;
        }
        else
            iter++;
    }

    return best;
}