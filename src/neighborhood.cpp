#include <vector>
#include <algorithm>
#include <random>
#include "neighborhood.h"
#include "constants.h"

using namespace std;

int best_k (int size) {
    int k = 0;
    while (BIN_SIZE[k] < size)
        k++;

    return k;
}

int is_feasible (Bin *b1, Bin *b2, int i1, int i2, int s1, int s2, int** G) {
    return (b1->s - s1 + s2 <= MAX_COST &&
            b2->s - s2 + s1 <= MAX_COST &&
            b1->is_feasible(G[i2]) &&
            b2->is_feasible(G[i1]));
}

int is_better (Bin *b1, Bin *b2, int k_ti, int k_t, int size) {
    float C_old, C_new, U_old, U_new;
    
    C_old = BIN_SIZE[b1->k] + BIN_SIZE[b2->k];
    C_new = BIN_SIZE[k_ti]  + BIN_SIZE[k_t];
                    
    if (C_old > C_new) return 1;
    if (C_old < C_new) return 0;
    
    U_old = max((float) b1->s / BIN_SIZE[b1->k], (float) b2->s / BIN_SIZE[b2->k]);
    U_new = max((float) (b1->s - size) / BIN_SIZE[k_ti], (float) (b2->s + size) / BIN_SIZE[k_t]);

    if (U_old < U_new) return 1;

    return 0;
}

int is_better (Bin *b1, Bin *b2, int k_ti, int k_t, int s1, int s2) {
    float C_old, C_new, U_old, U_new;
    
    C_old = BIN_SIZE[b1->k] + BIN_SIZE[b2->k];
    C_new = BIN_SIZE[k_ti]  + BIN_SIZE[k_t];
                    
    if (C_old > C_new) return 1;
    if (C_old < C_new) return 0;
    
    U_old = max((float) b1->s / BIN_SIZE[b1->k], (float) b2->s / BIN_SIZE[b2->k]);
    U_new = max((float) (b1->s - s1 + s2) / BIN_SIZE[k_ti], (float) (b2->s - s2 + s1) / BIN_SIZE[k_t]);

    if (U_old < U_new) return 1;

    return 0;
}

int reinsertion (Solution& sol, int n, int* v, int** G) {
    int i, i1, i2;
    int size, k_ti, k_t;
    Bin *bin1, *bin2;

    vector<int> V (n);
    for (i = 0; i < n; i++)
        V[i] = i;

    random_device rd;
    mt19937 g(rd());
    shuffle(V.begin(), V.end(), g);

    vector<int> V_t (n-1);
    for (i = 0; i < n-1; i++)
        V_t[i] = V[i];

    for (int ti = 0; ti < n; ti++) {
        i1 = V[ti];
        bin1 = sol[i1];

        if (ti) V_t[ti-1] = V[ti-1]; 
        if (ti < n-1) V_t[ti] = V[n-1];

        for (int item : bin1->items) {
            size = v[item];
            k_ti = best_k(bin1->s - size);

            for (int t = 0; t < n-1; t++) {
                i2 = V_t[t];
                bin2 = sol[i2];
            
                if (bin2->s + size <= MAX_COST && bin2->is_feasible(G[item])) {
                    k_t = best_k(bin2->s + size);

                    if (is_better(bin1, bin2, k_ti, k_t, size)) {
                        sol.reinsert(i1, i2, k_ti, k_t, item, size);
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

int swap (Solution& sol, int n, int* v, int** G) {
    int i, i1, i2;
    int size1, size2, k_ti, k_t;
    Bin *bin1, *bin2;

    vector<int> V (n);
    for (i = 0; i < n; i++)
        V[i] = i;

    random_device rd;
    mt19937 g(rd());
    shuffle(V.begin(), V.end(), g);

    vector<int> V_t (n-1);
    for (i = 0; i < n-1; i++)
        V_t[i] = V[i];

    for (int ti = 0; ti < n; ti++) {
        i1 = V[ti];
        bin1 = sol[i1];

        if (ti) V_t[ti-1] = V[ti-1]; 
        if (ti != n-1) V_t[ti] = V[n-1];

        for (int t = 0; t < n-1; t++) {
            i2 = V_t[t];
            bin2 = sol[i2];

            for (int item1 : bin1->items) {
                for (int item2 : bin2->items) {
                    size1 = v[item1];
                    size2 = v[item2];
                    
                    if (is_feasible(bin1, bin2, item1, item2, size1, size2, G)) {
                        k_ti = best_k(bin1->s - size1 + size2);
                        k_t  = best_k(bin2->s - size2 + size1);

                        if (is_better(bin1, bin2, k_ti, k_t, size1, size2)) {
                            sol.swap(i1, i2, k_ti, k_t, item1, item2, size1, size2);
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}