#include <numeric>
#include "greedy.h"

using namespace std;


float greedy1 (int item, int k, Bin& bin, Instance& instance, const int* bin_costs) {
    if (k == bin.k)
        return (float) 0.1 * (1 - (instance[item] + bin.s) / bin_costs[k]);

    return (float) (bin_costs[k] - bin_costs[bin.k]) / instance[item];
}

float greedy2 (int item, int k, Bin& bin, Instance& instance, const int* bin_costs) {
    return (float) bin_costs[k] / (instance[item] + bin.s);
}

GreedyF chooser_legacy (Instance& instance) {
    if      (instance.s >   35)
        return greedy2;
    else if (instance.d > 0.35)
        return greedy1;
    else if (instance.s > 10.5)
        return greedy1;
    else
        return greedy2;
}


Greedy::Greedy (
    Instance&  instance ,
    int        bin_types,
    const int* bin_costs,
    GreedyChooser chooser
) :
    bin_types (bin_types),
    bin_costs (bin_costs),
    max_cost  (bin_costs[bin_types-1]),

    instance  (instance),
    chooser   (chooser ),
    new_type  (new int  [instance.size()]),
    new_cost  (new float[instance.size()])
{
    set_news();
}

Greedy::~Greedy () {
    delete[] new_type;
    delete[] new_cost;
}

void Greedy::set_news () {
    int i, v, k;

    for (i = 0; i < instance.size(); i++) {
        v = instance[i];

        k = 0;
        while (bin_costs[k] < v)
            k++;

        new_type[i] = k;
        new_cost[i] = (float) bin_costs[k] / v;
    }
}

bool Greedy::can_alloc (int item, int k, Bin& bin) {
    return bin.is_feasible(instance[item], bin_costs[k], instance(item));
}

BestAlloc Greedy::find_best (Solution& sol, vector <int>& V) {
    int i, t, k;
    int item, size;
    float cost;

    Bin* bin;
    BestAlloc best;
    GreedyF   greedy = chooser(instance);

    size = V.size();
    best.cost = max_cost;
    cost      = max_cost;

    for (i = 0; i < size; i++) {
        item = V.at(i);

        for (t = 0; t < sol.size(); t++) {
            bin = sol[t];

            for (k = bin->k; k < bin_types; k++) {
                if (can_alloc (item, k, *bin)) {
                    cost = greedy(item, k, *bin, instance, bin_costs);

                    if (cost < best.cost)
                        best(i, t, k, cost);

                    break;
                }
            }
        }

        if (new_cost[item] < best.cost)
            best(i, sol.size(), new_type[item], new_cost[item]);
    }

    return best;
}

Solution Greedy::initial_solution () {
    vector <int> V    (instance.size());
    Solution solution (instance.size(), bin_costs);

    iota (V.begin(), V.end(),  0);
    greedy_solution (solution, V);

    return solution;
}

void Greedy::greedy_solution (Solution& sol, vector <int>& V) {
    int item;
    BestAlloc best;

    while (!V.empty()) {
        best = find_best(sol, V);

        item = V.at(best.i);
        sol.alloc(
            best.t,
            best.k,
            item  ,
            instance[item]
        );

        swap(V[best.i], V.back());
        V.pop_back();
    }
}