#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "bin.h"

using namespace std;

class Solution {
    int   n;
    int obj;
    const int* bin_costs;

    Bin** S;  // bins reference

    public:
        Solution  (int bins, const int* costs);
        ~Solution ();

        Bin*      operator [] (int b);
        Solution& operator =  (Solution& sol);

        void clear ();

        Bin* new_bin    (int t);
        void erase_bin  (int b);
        void adjust_bin (int b, int t);
        void reloc_bin  (int b, vector <int>* V);

        void alloc    (int b, int t, int i, int s);
        void dealloc  (int b, int t, int i, int s);
        int  reinsert (int b1, int b2, int t1, int t2, int i, int s);
        int  swap     (int b1, int b2, int t1, int t2, int i1, int i2, int s1, int s2);

        int  size     ();
        int  get_obj  ();
        void describe ();
};

#endif