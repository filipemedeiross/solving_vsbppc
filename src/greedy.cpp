#include <numeric>
#include "greedy.h"
#include "constants.h"

using namespace std;

Greedy::Greedy (Instance* new_instance) : instance(new_instance),
                                          new_type(new int  [new_instance->n]),
                                          new_cost(new float[new_instance->n]) {
    int i, k, v;

    for (i = 0; i < instance->n; i++) {
        v = instance->v[i];

        k = 0;
        while (BIN_SIZE[k] < v)
            k++;

        new_type[i] = k;
        new_cost[i] = (float) BIN_SIZE[k] / v;
    }
}

Solution* Greedy::initial_solution () {
    Solution* solution = new Solution (instance->n);

    vector <int> V (instance->n);
    iota(V.begin(), V.end(), 0 );

    greedy_solution (*solution, V, V.size());

    return solution;
}

void Greedy::greedy_solution (Solution& sol, vector <int>& V, int n) {
    int it, i, t, k, item;

    for (it = 0; it < n; it++) {
        find_best(sol, V, i, t, k, MAX_COST);

        if (t == sol.n)
            sol.new_bin(k);

        item = V.at(i);
        sol.alloc(t, k, item, instance->v[item]);

        V.erase(V.begin() + i);
    }
}

void Greedy::update_best (int& i, int& t, int& k, float& cost,
                          int _i, int _t, int _k, float _cost) {
    i = _i;
    t = _t;
    k = _k;
    cost = _cost;
}

void Greedy::find_best (Solution& sol, vector <int>& V, int& bi, int& bt, int& bk, float cost) {
    Bin* bin;
    int i, t, k, item;
    int size = V.size();
    float bcost =  cost;

    for (i = 0; i < size; i++) {
        item = V.at(i);

        for (t = 0; t < sol.n; t++) {
            bin = sol[t];

            for (k = 0; k < BIN_TYPES; k++) {
                if (instance->v[item] + bin->s <= BIN_SIZE[k] && bin->is_feasible(instance->G[item])) {
                    if (k == bin->k)
                        cost = (float) BIN_SIZE[k] / (instance->v[item] + bin->s) - 1;
                    else
                        cost = (float) (BIN_SIZE[k] - BIN_SIZE[bin->k]) / instance->v[item];

                    if (cost < bcost) 
                        update_best(bi, bt, bk, bcost,
                                    i , t , k , cost );
                }
            }
        }

        if (new_cost[item] < bcost)
            update_best(bi, bt, bk, bcost,
                        i , sol.n, new_type[item], new_cost[item]);
    }
}