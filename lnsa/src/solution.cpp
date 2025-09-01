#include <iostream>
#include "solution.h"

using namespace std;

Solution::Solution (int bins, const int* costs) :
    n              (0),
    obj            (0),
    bin_costs  (costs),
    S (new Bin*[bins])
{}

Solution::~Solution () {
    clear();

    delete [] S;
}

Bin* Solution::operator [] (int b) {
    if (b < n)
        return S[b];

    throw out_of_range("Index out of bounds");
}

Solution& Solution::operator = (Solution& sol) {
    if (this != &sol) {
        clear();

        for (int i = 0; i < sol.size(); i++) {
            n++;

            S[i] =  new Bin (*sol[i]);
            obj += bin_costs[S[i]->k];
        }
    }

    return *this;
}

void Solution::clear () {
    while (n) {
        n--;
        obj -= bin_costs[S[n]->k];

        delete S[n];
    }
}

Bin* Solution::new_bin (int t) {
    Bin* last = S[n] = new Bin(t);

    n++;
    obj += bin_costs[t];

    return last;
}

void Solution::erase_bin (int b) {
    Bin* bin = S[b];

    n--;
    obj -= bin_costs[bin->k];

    delete bin;

    if (b != n) {
        S[b] = S[n]   ;
        S[n] = nullptr;
    }
}

void Solution::adjust_bin (int b, int t) {
    int k = S[b]->k;

    if (t != k)
        obj += bin_costs[t] - bin_costs[k];
}

void Solution::reloc_bin (int b, vector <int>* V) {
    for (int item : S[b]->get_items())
        V->push_back(item);

    erase_bin(b);
}

void Solution::alloc (int b, int t, int i, int s) {
    if (b == n)
        new_bin(t);
    else
        adjust_bin(b, t);

    S[b]->add(i, s, t);
}

void Solution::dealloc (int b, int t, int i, int s) {
    int k = S[b]->k;

    if (t != k)
        obj -= bin_costs[k] - bin_costs[t];

    S[b]->remove(i, s, t);
}

int Solution::reinsert (int b1, int b2, int t1, int t2, int i, int s) {
    dealloc(b1, t1, i, s);
    alloc  (b2, t2, i, s);

    return i;
}

int Solution::swap (int b1, int b2, int t1, int t2, int i1, int i2, int s1, int s2) {
    reinsert(b1, b2, t1, t2, i1, s1);
    reinsert(b2, b1, t2, t1, i2, s2);

    return i2;
}

int Solution::size () {
    return n;
}

int Solution::get_obj () {
    return obj;
}

void Solution::describe () {
    cout << "Objective value = " << obj << endl;

    // Displaying non-empty bins
    for (int i = 0; i < n; i++)
        S[i]->describe(i);
}