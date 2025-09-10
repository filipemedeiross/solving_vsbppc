#include <random>
#include <cmath>
#include "bin.h"
#include "destroy.h"
#include "constants.h"

#define WEIGHT 8.74f
#define OFFSET 1.26f

using namespace std;

namespace {
    random_device  rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);
}

int max_gap (Solution& sol) {
    int n;
    int gap, max_gap;
    Bin* bin;

    n = sol.size();

    max_gap = 0;
    for (int i = 0; i < n; i++) {
        bin = sol[i];
        gap = BIN_SIZE[bin->k] - bin->s;

        max_gap = max(max_gap, gap);
    }

    return max_gap;
}

float prob_weight (Bin& bin, int max_gap) {
    if (!max_gap)
        return 0.1f;

    int   free = BIN_SIZE[bin.k] - bin.s;
    float coef = (float)  free / max_gap;

    return log10f(WEIGHT * coef + OFFSET);
}

vector <int> destroy_solution (Solution& sol, float p) {
    float  w;
    Bin* bin;
    vector <int> V;

    int idx = 0;
    int gap = max_gap(sol);
    while (idx < sol.size()) {
        bin = sol[idx];
        w   = prob_weight(*bin, gap);

        if (dis(gen) < p * w)
            sol.reloc_bin(idx, &V);
        else
            idx++;
    }

    return V;
}