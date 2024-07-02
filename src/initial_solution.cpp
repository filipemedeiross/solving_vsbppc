#include "initial_solution.h"
#include "constants.h"

using namespace std;

Greedy::Greedy (Instance* new_instance) {
    instance = new_instance;
    new_bins_type = new int[instance->n];
    new_bins_cost = new float[instance->n];
    
    for (int i = 0; i < instance->n; i++) {
        int k = 0;
        while (BIN_SIZE[k] < instance->v[i])
            k++;
        
        new_bins_type[i] = k;
        new_bins_cost[i] = (float) BIN_SIZE[k] / instance->v[i];
    }
}

Solution* Greedy::initial_solution () {
    Solution* solution = new Solution (instance->n);

    vector <int> V (instance->n);
    for (int i = 0; i < instance->n; i++)
        V[i] = i;

    greedy_solution (*solution, V, V.size());

    return solution;
}

void Greedy::update_best (int& i, int& t, int& k, float& cost, int _i, int _t, int _k, float _cost) {
    i = _i;
    t = _t;
    k = _k;
    cost = _cost;
}

void Greedy::find_best (Solution& sol, vector <int>& V, int& best_i, int& best_t, int& best_k, float initial_cost) {
    int item;
    float cost, best_cost;
    Bin* bin;

    best_cost = initial_cost;
    for (int i = 0; i < V.size(); i++) {
        item = V.at(i);

        for (int t = 0; t < sol.n; t++) {
            bin = sol[t];

            for (int k = 0; k < BIN_TYPES; k++) {
                if (instance->v[item] + bin->s <= BIN_SIZE[k] && bin->is_feasible(instance->G[item])) {
                    if (k == bin->k)
                        cost = (float) BIN_SIZE[k] / (instance->v[item] + bin->s) - 1;
                    else
                        cost = (float) (BIN_SIZE[k] - BIN_SIZE[bin->k]) / instance->v[item];

                    if (cost < best_cost) 
                        update_best(best_i, best_t, best_k, best_cost, i, t, k, cost);
                }
            }
        }

        if (new_bins_cost[item] < best_cost)
            update_best(best_i, best_t, best_k, best_cost, i, sol.n, new_bins_type[item], new_bins_cost[item]);
    }
}

void Greedy::greedy_solution (Solution& sol, vector <int>& V, int n_items) {
    int i, t, k;

    for (int it = 0; it < n_items; it++) {   
        find_best(sol, V, i, t, k, MAX_COST);

        if (t == sol.n)
            sol.new_bin(k);
        sol.alloc(t, k, V.at(i), instance->v[V.at(i)]);

        V.erase(V.begin() + i);
    }
}