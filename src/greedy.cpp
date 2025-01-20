#include <numeric>
#include "greedy.h"
#include "constants.h"

using namespace std;

Greedy::Greedy (Instance* new_instance) : dis(0.0, 1.0),
                                          gen(random_device{}()),
                                          instance(new_instance),
                                          new_type(new int  [new_instance->n]),
                                          new_cost(new float[new_instance->n]) {
    set_news();
    set_hc  ();
}

Greedy::~Greedy () {
    delete[] new_type;
    delete[] new_cost;
}

void Greedy::set_news () {
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

void Greedy::set_hc () {
    float p;

    if (instance->s > 35)
        p = 1.0;
    else if (instance->d > 0.35)
        p = 0.0;
    else if (instance->s > 10.5)
        p = 0.0;
    else
        p = 0.1;

    hc = get_prob() < p;
}

float Greedy::get_prob () {
    return dis(gen);
}

Solution* Greedy::initial_solution () {
    Solution* solution = new Solution (instance->n);

    vector <int> V (instance->n);
    iota(V.begin(), V.end(), 0 );

    greedy_solution (*solution, V, V.size());

    return solution;
}

float Greedy::greedy1 (int item, int k, Bin& bin) {
    if (k == bin.k)
        return (float) 0.1 * (1 - (instance->v[item] + bin.s) / BIN_SIZE[k]);

    return (float) (BIN_SIZE[k] - BIN_SIZE[bin.k]) / instance->v[item];
}

float Greedy::greedy2 (int item, int k, Bin& bin) {
    return (float) BIN_SIZE[k] / (instance->v[item] + bin.s);
}

void Greedy::greedy_solution (Solution& sol, vector <int>& V, int n) {
    int it, i, t, k, item;
    float (Greedy::*cb) (int, int, Bin&);

    cb = hc ? &Greedy::greedy2 :
              &Greedy::greedy1;

    for (it = 0; it < n; it++) {
        find_best(sol, V, i, t, k, MAX_COST, cb);

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

void Greedy::find_best (Solution& sol, vector <int>& V, int& bi, int& bt, int& bk, float cost, float (Greedy::*cb)(int, int, Bin&)) {
    Bin* bin;
    int i, t, k, item;
    int size = V.size();
    float bcost =  cost;

    for (i = 0; i < size; i++) {
        item = V.at(i);

        for (t = 0; t < sol.n; t++) {
            bin = sol[t];

            for (k = bin->k; k < BIN_TYPES; k++) {
                if (instance->v[item] + bin->s <= BIN_SIZE[k] && bin->is_feasible(instance->G[item])) {
                    cost = (this->*cb)(item, k, *bin);

                    if (cost < bcost)
                        update_best(bi, bt, bk, bcost,
                                    i , t , k , cost );
                    break;
                }
            }
        }

        if (new_cost[item] < bcost)
            update_best(bi, bt, bk, bcost,
                        i , sol.n, new_type[item], new_cost[item]);
    }
}