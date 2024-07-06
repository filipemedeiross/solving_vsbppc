#include <iostream>
#include "solution.h"
#include "constants.h"

using namespace std;

Solution::Solution (int bins) : n(0), obj(0), S(new Bin*[bins]) {}

Bin* Solution::operator [] (int b) {
    if (b < n)
        return S[b];

    throw out_of_range("Index out of bounds");
}

void Solution::copy (Solution& sol) {
    Bin *bin, *nbin;

    // Cleaning the bins
    while (n) erase_bin(n-1);

    // Copying solution 'sol'
    for (int i = 0; i < sol.n; i++) {
        bin = sol[i];

        nbin = new_bin(bin->k);
        nbin->s = bin->s;
        nbin->n = bin->n;
        for (int item : bin->items)
            nbin->items.push_back(item);
    }
}

Bin* Solution::new_bin (int t) {
    Bin* last = S[n] = new Bin(t);

    n++;
    obj += BIN_SIZE[t];

    return last;
}

void Solution::erase_bin (int b) {
    Bin* bin = S[b];

    n--;
    obj -= BIN_SIZE[bin->k];

    delete bin;

    if (b != n) {
        S[b] = S[n];
        S[n] = nullptr;
    }
}

void Solution::alloc (int b, int t, int i, int s) {
    int k = S[b]->k;

    if (t != k)
        obj += BIN_SIZE[t] - BIN_SIZE[k];

    S[b]->add(i, s, t);
}

void Solution::dealloc (int b, int t, int i, int s) {
    int k = S[b]->k;

    if (t != k)
        obj -= BIN_SIZE[k] - BIN_SIZE[t];

    S[b]->remove(i, s, t);
}

void Solution::reinsert (int b1, int b2, int t1, int t2, int i, int s) {
    dealloc(b1, t1, i, s);
    alloc  (b2, t2, i, s);
}

void Solution::swap (int b1, int b2, int t1, int t2, int i1, int i2, int s1, int s2) {
    reinsert(b1, b2, t1, t2, i1, s1);
    reinsert(b2, b1, t2, t1, i2, s2);
}

void Solution::describe () {
    cout << "Objective value = " << obj << endl;

    // Displays non-empty bins
    for (int i = 0; i < n; i++) {
        cout << "Bin " << i << " ";
        S[i]->describe();
    }
}