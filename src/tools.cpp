#include <random>
#include <cmath>
#include "tools.h"
#include "bin.h"
#include "constants.h"

using namespace std;

int max_gap (Solution& sol) {
    Bin* bin;
    int i, gap, max_gap;

    max_gap = 0;
    for (i = 0; i < sol.n; i++) {
        bin = sol[i];
        gap = BIN_SIZE[bin->k] - bin->s;

        if (max_gap < gap)
            max_gap = gap;
    }

    return max_gap;
}

float prob_weight (Bin* bin, int max_gap) {
    int free;
    float coef;

    free = BIN_SIZE[bin->k] - bin->s;
    coef = (float) free / max_gap;

    return log10(8.74 * coef + 1.25);
}

vector <int>* destroy_solution (Solution& sol, float p) {
    int idx;
    float w;
    Bin* bin;

    int gap = max_gap(sol);
    vector <int>* V = new vector <int>();

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    idx = 0;
    while (idx < sol.n) {
        bin = sol[idx];
        w   = prob_weight(bin, gap);

        if (dis(gen) < p * w)
            sol.reloc_bin(idx, V);
        else
            idx++;
    }

    return V;
}