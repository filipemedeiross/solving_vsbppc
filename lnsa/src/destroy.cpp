#include <random>
#include <cmath>
#include "bin.h"
#include "destroy.h"
#include "constants.h"

#define WEIGHT 8.74f
#define OFFSET 1.26f

using namespace std;

int max_gap (Solution& sol) {
    int n;
    int gap, max_gap;
    Bin* bin;

    n = sol.size();

    max_gap = 0;
    for (int i = 0; i < n; i++) {
        bin = sol[i];
        gap = BIN_SIZE[bin->k] - bin->s;

        if (max_gap < gap)
            max_gap = gap;
    }

    return max_gap;
}

float prob_weight (Bin& bin, int max_gap) {
    int   free = BIN_SIZE[bin.k] - bin.s;
    float coef = (float)  free / max_gap;

    return log10f(WEIGHT * coef + OFFSET);
}

vector <int>* destroy_solution (Solution& sol, float p) {
    float  w;
    Bin* bin;

    int gap = max_gap(sol);
    vector <int>* V = new vector <int>();

    static random_device  rd;
    static mt19937 gen(rd());
    static uniform_real_distribution <float> dis(0.0f, 1.0f);

    int idx = 0;
    while (idx < sol.size()) {
        bin = sol[idx];
        w   = prob_weight(*bin, gap);

        if (dis(gen) < p * w)
            sol.reloc_bin(idx, V);
        else
            idx++;
    }

    return V;
}