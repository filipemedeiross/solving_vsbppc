#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "bin.h"

using namespace std;

class Solution {
    public:
        int   n;  // number of bins
        int obj;  // objective value
        Bin** S;  // bins reference

        Solution (int bins);
        ~Solution ();

        Bin* operator []  (int b);
        void copy (Solution& sol);

        void clear ();
        Bin* new_bin   (int t);
        void erase_bin (int b);
        void reloc_bin (int b, vector <int>* V);

        void alloc    (int b, int t, int i, int s);
        void dealloc  (int b, int t, int i, int s);
        int  reinsert (int b1, int b2, int t1, int t2, int i, int s);
        int  swap     (int b1, int b2, int t1, int t2, int i1, int i2, int s1, int s2);

        void describe ();
};

#endif