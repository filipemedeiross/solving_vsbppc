#include <iostream>
#include "solution.h"
#include "constants.h"

using namespace std;

Solution::Solution (int bins) {
    n = 0;
    obj = 0;
    S = new Bin*[bins];
}

Bin* Solution::operator [] (int bin) {
    if (bin >= 0 && bin < n)
        return S[bin];
    else
        throw out_of_range("Index out of bounds");
}

void Solution::copy (Solution& sol) {
    Bin *bin, *n_bin;

    // Cleaning the bin
    while (n) erase_bin(n-1);

    // Copying solution 'sol'
    for (int i = 0; i < sol.n; i++) {
        bin = sol[i];
        new_bin(bin->k);

        n_bin = S[i];
        n_bin->s = bin->s;
        n_bin->n = bin->n;
        for (int item : bin->items)
            n_bin->items.push_back(item);
    }
}

void Solution::new_bin (int type) {
    S[n] = new Bin(type);
    n++;
    obj += BIN_SIZE[type];
}

void Solution::erase_bin (int bin) {
    n--;
    obj -= BIN_SIZE[S[bin]->k];

    delete S[bin];
    S[bin] = S[n];
    S[n]   = nullptr;
}

void Solution::alloc (int bin, int type, int item, int size) {
    int k = S[bin]->k;

    if (type != k)
        obj += (BIN_SIZE[type] - BIN_SIZE[k]);

    S[bin]->add(item, size, type);
}

void Solution::dealloc (int bin, int type, int item, int size) {
    int k = S[bin]->k;

    if (type != k)
        obj -= (BIN_SIZE[k] - BIN_SIZE[type]);

    S[bin]->remove(item, size, type);
}

void Solution::reinsert (int bin1, int bin2, int type1, int type2, int item, int size) {
    dealloc(bin1, type1, item, size);
    alloc(bin2, type2, item, size);
}

void Solution::swap (int bin1, int bin2, int type1, int type2, int item1, int item2, int size1, int size2) {
    reinsert(bin1, bin2, type1, type2, item1, size1);
    reinsert(bin2, bin1, type2, type1, item2, size2);
}

void Solution::describe () {
    cout << "Objective value = " << obj << endl;

    // Displays non-empty bins
    for (int i = 0; i < n; i++) {
        cout << "Bin " << i << " ";
        S[i]->describe();
    }
}